#include "ServerSocket.h"
#include "SocketException.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include "OpenNI.h"
#include "OniSampleUtilities.h"
#include <iomanip>
#include <sstream>
#include <arpa/inet.h>
#define SAMPLE_READ_WAIT_TIMEOUT 2000 //2000ms

using namespace openni;

int main (){
  std::cout << "running....\n";
  float wX = 0, wY = 0, wZ = 0;
  Status rc = OpenNI::initialize();
  char buffer [50000];
  int n=0;

Device device;
rc = device.open(ANY_DEVICE);
VideoStream depth;
rc = depth.create(device, SENSOR_DEPTH);
rc = depth.start();
VideoFrameRef frame;
int changedStreamDummy;
VideoStream* pStream = &depth;


  try
    {
      // Create the socket
      ServerSocket server ( 30000 );

      while ( true )
	{

	  ServerSocket new_sock;
	  server.accept ( new_sock );

	  try
	    {
	      while ( true )
		{
		  std::string data;
		  new_sock >> data;

		  if(data == "k") 
			{
			  
			  
 // inicio openni2

		
		rc = OpenNI::waitForAnyStream(&pStream, 1, &changedStreamDummy, SAMPLE_READ_WAIT_TIMEOUT);
		rc = depth.readFrame(&frame);
		
		DepthPixel* pDepth = (DepthPixel*)frame.getData();

		int middleIndex = (frame.getHeight()+1)*frame.getWidth()/2;

                // EMANOEL PART.
		for(int i=0; i<640; i++){
                openni::CoordinateConverter::convertDepthToWorld(depth, i, 240,
                pDepth[(640*240)+i], &wX, &wY, &wZ );

		printf("(%2f %2f %2f)", wX, wY, wZ);
		printf("\n");


		n += sprintf(&buffer[n], "%.2f,%.2f,%.2f;", wX, wY, wZ);

		}
		//printf("%d %d\n", frame.getHeight(), frame.getWidth());
            	//printf("a distancia do pixel é %gmm " "localizado em %gmmx%gmm\r\n"
                //,wZ, wX, wY);

              

//fim openni2
			n = 0;
			new_sock << buffer;
						

			}
 		 
		}
	    }
	  catch ( SocketException& ) {}

	}
    }
  catch ( SocketException& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }
	
	depth.stop();
	depth.destroy();
	device.close();
	OpenNI::shutdown();

  return 0;
}
