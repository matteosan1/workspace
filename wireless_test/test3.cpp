#include <iwlib.h>
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
  wireless_scan_head head;
  wireless_scan *result;
  iwrange range;
  int sock;
  char wifi_name[6]={'w','l','p','2','s','0'};

  /* Open socket to kernel */
  sock = iw_sockets_open();

  /* Get some metadata to use for scanning */
  if (iw_get_range_info(sock, wifi_name , &range) < 0)
    {
      cout<<"Error during iw_get_range_info. Aborting."<<endl;
      return -1;
    }

  /* Perform the scan */
  if (iw_scan(sock, wifi_name, range.we_version_compiled, &head) < 0)
    {
      cout<<"Error during iw_scan. Aborting."<<endl;
      return -1;
    }
  
  /* List the resulted network */
  result = head.result;
  cout << "Wireless Feature Test" << endl;
  while (NULL != result)
    {
    //   while (1)
    //	{

      cout << result->b.essid << endl;
      result = result->next;
    }
  return 0;
}
