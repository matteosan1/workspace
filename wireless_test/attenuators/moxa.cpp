#include "moxa.h"

#include <string>
#include <iostream>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

int testMOXA() {
  
  while(1) {
    sleep(2);
    netsnmp_session session;
    init_snmp("connection_to_access_point");
    
    char ip[20];
    sprintf(ip, "192.168.127.253");
    std::cout << "Access Point " << ip << std::endl;
    
    snmp_sess_init(&session);
    session.peername = strdup(ip);
    session.version = SNMP_VERSION_2c;
    char a[10];
    sprintf(a, "%s", "public");
    session.community = (unsigned char*) a;
    session.community_len = strlen(a);
    
    netsnmp_session *ss;
    netsnmp_pdu *pdu, *response;
    
    oid anOID[MAX_OID_LEN];
    size_t anOID_len;
    
    SOCK_STARTUP;
    ss = snmp_open(&session);
    if (!ss) {
      //snmp_sess_perror("ack", &session);
      SOCK_CLEANUP;
      std::cout << "Cannot connect to SNMP server " << std::endl;
      return -1;
    }

    //pdu = snmp_pdu_create(SNMP_MSG_GETBULK);
    pdu = snmp_pdu_create(SNMP_MSG_GETBULK);
    pdu->non_repeaters = 0;
    pdu->max_repetitions = 15;
    anOID_len = MAX_OID_LEN;

    char* oids[4] = { "3", "4", "5", "6" };
    for (int nOids=0; nOids<4; nOids++) {
      char oidString[200];
      sprintf(oidString, "%s.%s.0", ".1.3.6.1.4.1.8691.15.70.1.11.17.1", oids[nOids]);
      //sprintf(oidString, "%s", ".1.3.6.1.4.1.8691.15.70.1.11.17.1");

      if (!snmp_parse_oid(oidString, anOID, &anOID_len)) {
	std::cout << "Error for OID: " << oidString << std::endl;
      }
    
      snmp_add_null_var(pdu, anOID, anOID_len);
    }
    
    int status = snmp_synch_response(ss, pdu, &response);
    
    if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR) {
      netsnmp_variable_list* vars = response->variables;
      
      int index = 0;
      for (vars=response->variables; vars; vars =vars->next_variable) {
	if (index == 0 || index == 3)		
	  {
	  if (vars->type == ASN_OCTET_STR) {
	    char *sp = (char *)malloc(1 + vars->val_len);
	    memcpy(sp, vars->val.string, vars->val_len);
	    sp[vars->val_len] = '\0';
	    std::cout << "Mac: " << sp << " ";
	    free(sp);
	  }
	}
	if (index == 1 || index == 2)
	  {
	    if (vars->type == ASN_INTEGER) {
	      std::cout << "Power: " <<*(vars->val.integer) << std::endl;
	    }
	  }
	index++;
      }
    } else {
      if (status == STAT_SUCCESS) {
	std::cout << "Error in packet. Reason: " << snmp_errstring(response->errstat) << std::endl;
      }
      else if (status == STAT_TIMEOUT) {
	std::cout << "Timeout: no response from " << std::endl;
      } else {
	std::cout << "Error in reading SNMP" << std::endl;
      }
    }
    std::cout << std::endl;
    
    if (response)
      snmp_free_pdu(response);
    
    snmp_close(ss);
    
    SOCK_CLEANUP;
  }

  return 0;
}
  
