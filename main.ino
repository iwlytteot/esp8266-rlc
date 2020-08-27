#include <ESP8266WiFi.h>

#define RED 4
#define GREEN 5
#define BLUE 0

char ssid[] = "";
char password[] = "";
int wl_status = WL_DISCONNECTED;

WiFiServer server( 5432 );
WiFiClient client;

void setup() { 

  Serial.begin( 115200 );
  pinMode( RED, OUTPUT );
  pinMode( GREEN, OUTPUT );
  pinMode( BLUE, OUTPUT );

  
  IPAddress staticIP(192, 168, 1, 51);
  IPAddress subnet(255, 255, 255, 0);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress dns(8, 8, 8, 8);
  WiFi.config(staticIP, subnet, gateway, dns);
  
  do {
    wl_status = WiFi.begin( ssid, password );
    delay( 5000 );
    analogWrite( RED, 700 );
    delay( 300 );
    analogWrite( RED, 0 );
  } while ( wl_status != WL_CONNECTED );
  
  server.begin(); // Now this device is available on 192.168.1.200:5432 for TCP connection
  analogWrite( RED, 700 );
  
}

void set_led( int red, int green, int blue ) {
  analogWrite( RED, red );
  analogWrite( GREEN, green );
  analogWrite( BLUE, blue );
}

void check_available_client() {
  if ( client )
    return;
  client = server.available();
}

void dimming( int *rgb ) {
  int rgb_step[ 3 ];  
  rgb_step[ 0 ] = rgb[ 3 ] - rgb[ 0 ];
  rgb_step[ 1 ] = rgb[ 4 ] - rgb[ 1 ];
  rgb_step[ 2 ] = rgb[ 5 ] - rgb[ 2 ];

  int rgb_new[ 3 ] = { rgb[ 0 ], rgb[ 1 ], rgb[ 2 ] };
  int highest = max( max( abs( rgb_step[ 0 ] ), abs( rgb_step[ 1 ] ) ), abs( rgb_step[ 2 ] ) );
  bool state[ 3 ];

  int rgb_correction[ 3 ];
  for ( int i = 0; i < 3; ++i ) {
    state[ i ] = rgb_step[ i ] < 0;
    if ( rgb_step[ i ] == 0 ) {
      rgb_correction[ i ] = 1025;
      rgb_step[ i ] = 1025;
    }
    else {
      int r_step = 10 * double( highest ) / abs( rgb_step[ i ] );
      if ( r_step == 10 ) {
        rgb_correction[ i ] = 1025;
        rgb_step[ i ] = 1;
      }
      else {
        rgb_correction[ i ] = 11 - ( r_step % 10 );
        rgb_step[ i ] = ( r_step - ( r_step % 10 ) ) / 10;
      }
    }
  }
  
  

  int rgb_count[ 3 ] = { 0 };
  int count = 1;
  bool change = false;
  while ( !client ) {
    for ( int i = 0; i < 3; ++i ) {
      if ( count % rgb_step[ i ] == 0 ) {
        if ( ++rgb_count[ i ] % rgb_correction[ i ] == 0 )
          continue;
        if ( change )
          rgb_new[ i ] += state[ i ] ? 1 : -1;
        else
          rgb_new[ i ] += state[ i ] ? -1 : 1;
      }
    }
    set_led( rgb_new[ 0 ], rgb_new[ 1 ], rgb_new[ 2 ] );
    
    delay( rgb[ 7 ] );
    
    if ( count >= highest && change )
      break;
    else if ( count >= highest ) {
      Serial.print( "From ");
      Serial.print( rgb[ 1 ] );
      Serial.print( " to ");
      Serial.print( rgb_new[ 1 ] );
      Serial.print( " of highest: " );
      Serial.print( highest );
      Serial.print( " state: " );
      Serial.println( state[ 1 ] );
      change = true; count = 1;
    } 
    else
      ++count;

    check_available_client();
  }
}

void handle_message( const String &line ) {
  String part = "";
  byte count = 0;
  int rgb[8] = { 0 }; // | start: R G B (0, 1, 2 indexes), end: R G B (3, 4, 5 indexes), mode (6), speed (7) |
  for ( char c : line ) {
    if ( c == '.' ) {
      rgb[ count ] = part.toInt();
      if ( count < 6 )
        rgb[ count ] *= 4;
      ++count;
      part = "";
    } else {
      part += c;
    }  
  }
  if ( rgb[ 6 ] == 0 ) { set_led( rgb[0], rgb[1], rgb[2] ); }
  if ( rgb[ 6 ] == 1 ) { while ( !client ) dimming( rgb ); }
}

void loop() {
  
  check_available_client();
  if ( client.connected() ) {
    String line = client.readStringUntil('\n');
    client.stop();
    handle_message( line );
  } 
}
