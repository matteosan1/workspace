#include "oring.h"

#include <string>
#include <iostream>

#include <net-snmp/net-snmp-config.h>
#include <net-snmp/net-snmp-includes.h>

#include <time.h>

const std::string currentDateTime() {

  time_t now = time(0);
  struct tm tstruct;
  char buf[80];
  tstruct = *localtime(&now);
  strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

  return buf;
}

int testOring() {

  char* oids[4] = { "2.0", "3.0", "5.0", "6.0" };
  
  while(1) {
    sleep(2);
    netsnmp_session session;
    init_snmp("connection_to_access_point");
    
    char ip[20];
    sprintf(ip, "192.168.204.6");
    //std::cout << "Access Point " << ip << std::endl;
    
    snmp_sess_init(&session);
    session.peername = strdup(ip);
    session.version = SNMP_VERSION_2c;
    char a[10];
    sprintf(a, "%s", "private");
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

    std::cout << currentDateTime() << " ";
    pdu = snmp_pdu_create(SNMP_MSG_GETBULK);
    //pdu = snmp_pdu_create(SNMP_MSG_GET);
    pdu->non_repeaters = 0;
    pdu->max_repetitions = 15;
    anOID_len = MAX_OID_LEN;

    for (int nOids=0; nOids<4; nOids++) {
   
      char oidString[200];
      sprintf(oidString, "%s%s", ".1.3.6.1.4.1.25972.100.2.0.0.5.", oids[nOids]);
    
      if (!snmp_parse_oid(oidString, anOID, &anOID_len)) {
	std::cout << "Error for OID: " << oidString << std::endl;
      }
      
      snmp_add_null_var(pdu, anOID, anOID_len);
    }

    int status = snmp_synch_response(ss, pdu, &response);
    
    int count = 0;
    netsnmp_variable_list* vars = response->variables;
    for (vars=response->variables; vars; vars =vars->next_variable) {
      //	vars = response->variables;
      std::cout << count << std::endl;
      if (status == STAT_SUCCESS && response->errstat == SNMP_ERR_NOERROR) {
	if (count == 0) {
	  //if (vars->type == ASN_OCTET_STR) {
	  char *sp = (char *)malloc(1 + vars->val_len);
	  memcpy(sp, vars->val.string, vars->val_len);
	  sp[vars->val_len] = '\0';
	  std::cout << "SSID: " << sp << " "; //vars->val.string << " ";
	  free(sp);
	}

	if (count > 1) 
	  std::cout << " Channel: " << *(vars->val.integer);
	if (count == 2) 
	  std::cout << " TxPower: " << *(vars->val.integer);
	if (count == 3) 
	  std::cout << " Status: " << *(vars->val.integer);	
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
      count++;
    }

    std::cout << std::endl;

    if (response)
      snmp_free_pdu(response);
    
    snmp_close(ss);
    
    SOCK_CLEANUP;

  }

  return 0;
}
