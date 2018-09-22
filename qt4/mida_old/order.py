# -*- coding: utf-8 -*-

class Order:
  """Class to manage the orders"""
  PROPSHEETPAGE* ps;
  Result result;
  Result result2;
  Row row_temp;
  Connection* c;
  vector<Row> edit;
  
  sql_create_21(ordine_riepilogo, 3, 21,
  int, indice,
  int, fatture,
  string, data,
  int, quantita,
  int, indice_cliente,
  int, indirizzo,
  int, pagamento,
  float, prezzo,
  float, spedizione,
  float, spedizione_vera,
  float, sconto,
  string, nota,
  int, pagato,
  int, spedito,
  int, euroiva,
  int, porto,
  int, aspetto,
  int, colli,
  float, peso,
  string, data_invio,
  string, trasporto);
  
  sql_create_5(ordini, 4, 5, int, indice_ordine, int, indice_CD, 
  string, codice, 	
  int, quantita,
  float, prezzo);
  
  BOOL CALLBACK VcDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
  
  ViewClient* vc;
  
  def __init__(self):
    data = "";
    indirizzo = 0;
    quantita = 0;
    prezzo = 0.0;
    ordine = 0;
    prezzo_netto = 0.0;
    pagato = false;
    spedito = false;
    numero_fattura = 0;
    spedizione_posta = 0.0;
    insert = h;
    c = q;
    Query query = c->query();
    query << "select * from clienti order by cognome, nome";
    result = query.store();    
  
  
  
  
  
  
  
  
  

  virtual ~Order();
  vector<int> GetQuantitaParziali() { return cd_collo; };
  int GetIndirizzo() { return indirizzo; };
  float GetPrezzo() { return prezzo; };
  float GetSconto() { return sconto; };
  float GetSpedizione() { return spedizione; };
  float GetSpedizionePosta() { return spedizione_posta; };
  bool GetPagato() { return pagato; };
  bool GetSpedito() { return spedito; };
  int GetQuantita() { return quantita; };
  int GetFattura() { return numero_fattura; };
  int GetCliente() { return cliente; };
  int GetTipoPagamento() { return tipo_pagamento; };
  int GetOrdine() { return ordine; };
  string GetData() { return data; };
  string GetNota() { return nota; };
  void FillCombo();
  void InsertInOrder(Row row);
  void DeleteFromOrder();
  void OnExit();
  void OnSearchOrders();
  void OnFillOrder();
  void OnChangePrice();
  BOOL CALLBACK DlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
  HWND hwndCtl;
  
      
      BOOL CALLBACK Order::DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
      {
	HWND hBtn1, hBtn2;
	switch (Message)
	{            
	case WM_NOTIFY:
	  switch(((NMHDR FAR *) lParam)->code)
	  {
	    case PSN_KILLACTIVE:
	      SetWindowLong(hwnd, DWL_MSGRESULT, FALSE);
	      return true;
	      break;
	      case PSN_APPLY:
		OnExit();
		break;
		}       
		
		case WM_COMMAND:
		  if ((HIWORD(wParam) == EN_KILLFOCUS) && ((LOWORD(wParam) == IDC_REDUCTION) ||
		  (LOWORD(wParam) == IDC_SHIPPMENT) || (LOWORD(wParam) == IDC_SHIPPMENT2)))
		  OnChangePrice();
		  if ((HIWORD(wParam) == CBN_SELCHANGE) && (LOWORD(wParam) == IDC_COMBO_CLIENT))
		  {
		    if (insert)
		    {
		      HWND hCombo = GetDlgItem(hwndCtl, IDC_COMBO_CLIENT); 
		      int indice = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
		      Row r = *(result.begin()+indice);
		      cliente = (int)r[0];
		      hBtn1 = GetDlgItem(hwndCtl, ID_INFO);
		      EnableWindow(hBtn1, true);
		      }
		      else
		      {
			string s = "";
			hBtn1 = GetDlgItem(hwndCtl, IDC_PRICE); 
			SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
			hBtn1 = GetDlgItem(hwndCtl, IDC_REDUCTION); 
			SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
			hBtn1 = GetDlgItem(hwndCtl, IDC_QUANTITY); 
			SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
			hBtn1 = GetDlgItem(hwndCtl, IDC_NOTE); 
			SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) nota.c_str()); 
			hBtn1 = GetDlgItem(hwndCtl, IDC_SHIPPMENT); 
			SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
			hBtn1 = GetDlgItem(hwndCtl, IDC_SHIPPMENT2);
			SendMessage(hBtn1, WM_SETTEXT, 0, (LPARAM) s.c_str()); 
			CheckRadioButton(hwndCtl, IDC_RADIO_ADR1, IDC_RADIO_ADR2, 0);
			SendDlgItemMessage(hwndCtl, IDC_LIST, LB_RESETCONTENT, 0, 0);
			OnSearchOrders();
			}
			}
			if ((HIWORD(wParam) == CBN_SELCHANGE) && (LOWORD(wParam) == IDC_COMBO_DATA))
			{
			  OnFillOrder();
			  }        
			  if ((HIWORD(wParam) == LBN_DBLCLK) && (LOWORD(wParam) == IDC_LIST))
			  if (quantita != 0)
			  DeleteFromOrder();
			  if (HIWORD(wParam) == BN_CLICKED)
			  { 
			  if (LOWORD(wParam) == ID_INFO)
			  {
			    HWND hCombo = GetDlgItem(hwndCtl, IDC_COMBO_CLIENT); 
			    int indice = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
			    Row r = *(result.begin() + indice);
			    vc = new ViewClient(r);
			    DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INSERT_CLIENT), hwndCtl, VcDlgProc);
			    delete vc;
			    }
			    }            
			    return true;    
			    case WM_INITDIALOG:
			      hwndCtl = hwnd;
			      ps = (PROPSHEETPAGE*)lParam;
			      FillCombo();
			      return true;
			      default:
				return false;
				}
				} 
				
				
				
				
				
				
				
				void Order::OnFillOrder()
				{
				  HWND hCombo = GetDlgItem(hwndCtl, IDC_COMBO_DATA); 
				  int indice = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				  Row r = *(result2.begin()+indice);
				  ordine = (int)r[0];
				  int decimal, segno; 
				  char b[3];
				  
				  prezzo = (float)r[7];
				  string s = _ecvt(prezzo, 6, &decimal, &segno);
				  s.insert(decimal, ".");
				  string s1 = s.substr(0, decimal+3);
				  hCombo = GetDlgItem(hwndCtl, IDC_PRICE); 
				  SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s1.c_str()); 
				  
				  sconto = (float)r[10];
				  s = _ecvt(sconto, 6, &decimal, &segno);
				  s.insert(decimal, ".");
				  s1 = s.substr(0, decimal+3);
				  hCombo = GetDlgItem(hwndCtl, IDC_REDUCTION); 
				  SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s1.c_str()); 
				  
				  spedizione = (float)r[8];
				  s = _ecvt(spedizione, 6, &decimal, &segno);
				  s.insert(decimal, ".");
				  s1 = s.substr(0, decimal+3);
				  hCombo = GetDlgItem(hwndCtl, IDC_SHIPPMENT); 
				  SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s1.c_str()); 
				  
				  spedizione_posta = (float)r[9];
				  s = _ecvt(spedizione_posta, 6, &decimal, &segno);
				  s.insert(decimal, ".");
				  s1 = s.substr(0, decimal+3);
				  hCombo = GetDlgItem(hwndCtl, IDC_SHIPPMENT2); 
				  SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s1.c_str()); 
				  
				  quantita = (int)r[3];
				  s = itoa(quantita, b, 10);
				  hCombo = GetDlgItem(hwndCtl, IDC_QUANTITY); 
				  SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) s.c_str());
				  
				  nota = (string)r[11];
				  hCombo = GetDlgItem(hwndCtl, IDC_NOTE); 
				  SendMessage(hCombo, WM_SETTEXT, 0, (LPARAM) nota.c_str());
				  
				  data = (string)r[2];
				  
				  
				  if ((int)r[12])
				  CheckDlgButton(hwndCtl, IDC_CHECK_PAID, BST_CHECKED);
				  else    
				  CheckDlgButton(hwndCtl, IDC_CHECK_PAID, BST_UNCHECKED);
				  if ((int)r[13])
				  CheckDlgButton(hwndCtl, IDC_CHECK_SENT, BST_CHECKED);   
				  else
				  CheckDlgButton(hwndCtl, IDC_CHECK_SENT, BST_UNCHECKED);       
				  
				  numero_fattura = (int)r[1];
				  indirizzo = (int)r[5];           
				  CheckRadioButton(hwndCtl, IDC_RADIO_ADR1, IDC_RADIO_ADR2, IDC_RADIO_ADR1+(int)r[5]);
				  
				  cd_collo.clear();
				  edit.clear();
				  Query query = c->query();
				  query << "select * from ordini where indice_ordine='" << ordine << "' order by indice_CD";
				  Result res_temp_1 = query.store();
				  Result res_temp_2;
				  Result::iterator i, j;
				  SendDlgItemMessage(hwndCtl, IDC_LIST, LB_RESETCONTENT, 0, 0);
				  string linea;
				  hCombo = GetDlgItem(hwndCtl, IDC_LIST); 
				  for(i=res_temp_1.begin(); i!=res_temp_1.end(); i++)
				  {
				    r = *i;
				    cd_collo.push_back((int)r[3]);
				    query << "select * from cd where indice='" << (int)r[1] << "'";
				    result2 = query.store();
				    row_temp = *result2.begin();
				    edit.push_back(row_temp);
				    linea = (string)r[3] + " - " + (string)row_temp[2] + " " + (string)row_temp[1];
				    SendMessage(hCombo, LB_ADDSTRING, 0, (LPARAM) linea.c_str());
				    }   
				    }
				    
				    void Order::OnSearchOrders()
				    {
				      HWND hCombo = GetDlgItem(hwndCtl, IDC_COMBO_CLIENT); 
				      int indice = SendMessage(hCombo, CB_GETCURSEL, 0, 0);
				      Row r = *(result.begin()+indice);
				      cliente = (int)r[0];
				      string linea;
				      Query query = c->query();
				      query << "select * from ordine_riepilogo where indice_cliente='" << cliente << "' order by data";
				      result2 = query.store();
				      if (result2.size() != 0)
				      {
					Result::iterator i;
					hCombo = GetDlgItem(hwndCtl, IDC_COMBO_DATA); 
					SendDlgItemMessage(hwndCtl, IDC_COMBO_DATA, CB_RESETCONTENT, 0, 0);
					
					for(i=result2.begin(); i!=result2.end(); i++)
					{
					  r = *i;
					  linea = (string)r[2];
					  SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM) linea.c_str());
					  }                           
					  }
					  }
					  
					  void Order::OnExit()
					  {
					    TCHAR* passwd;
					    HWND hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT);   
					    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
					    if (nLen == 0)
					    spedizione = 0.0;
					    else
					    {         
					    passwd = new TCHAR[nLen+1]; 
					    GetWindowText(hEdit, passwd, nLen+1);
					    spedizione = atof(passwd);
					    }
					    
					    hEdit = GetDlgItem(hwndCtl, IDC_REDUCTION);   
					    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
					    if (nLen == 0)
					    sconto = 0.0;
					    else
					    {         
					    passwd = new TCHAR[nLen+1]; 
					    GetWindowText(hEdit, passwd, nLen+1);
					    sconto = atof(passwd);
					    }
					    
					    hEdit = GetDlgItem(hwndCtl, IDC_PRICE);
					    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
					    if (nLen == 0)
					    prezzo= 0.0;
					    else
					    {         
					    passwd = new TCHAR[nLen+1]; 
					    GetWindowText(hEdit, passwd, nLen+1);
					    prezzo = atof(passwd);
					    }
					    
					    hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT2);
					    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
					    if (nLen == 0)
					    spedizione_posta= 0.0;
					    else
					    {         
					    passwd = new TCHAR[nLen+1]; 
					    GetWindowText(hEdit, passwd, nLen+1);
					    spedizione_posta = atof(passwd);
					    }
					    
					    hEdit = GetDlgItem(hwndCtl, IDC_NOTE);
					    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
					    if (nLen == 0)
					    nota = "";
					    else
					    {         
					    passwd = new TCHAR[nLen+1]; 
					    GetWindowText(hEdit, passwd, nLen+1);
					    nota = passwd;
					    }
					    
					    if (IsDlgButtonChecked(hwndCtl, IDC_CHECK_SENT) == BST_CHECKED)
					    spedito = true;
					    else
					    spedito = false;
					    
					    if (IsDlgButtonChecked(hwndCtl, IDC_CHECK_PAID) == BST_CHECKED)
					    pagato = true;
					    else
					    pagato = false;
					    
					    if (!insert)
					    {
					      Query query = c->query();
					      query << "update ordine_riepilogo set nota = '" << nota << "' where indice = '" << ordine << "'";    
					      query.execute();
					      query << "update ordine_riepilogo set pagato = '" << pagato << "' where indice = '" << ordine << "'";    
					      query.execute();
					      query << "update ordine_riepilogo set spedito = '" << spedito << "' where indice = '" << ordine << "'";    
					      query.execute();
					      }
					      
					      if(insert)
					      {
						int indice;
						Query query = c->query();
						ordine_riepilogo riga;
						query << "select max(indice) as indice from ordine_riepilogo"; 
						Result res = query.store(); 
						Row r = *(res.begin());
						if ((string)r[0] == "NULL")
						indice = 0;
						else 
						indice = (int)r[0]+1;
						
						riga.indice = indice; riga.data = data;
						riga.quantita = quantita; riga.indice_cliente = cliente;            
						riga.indirizzo = indirizzo; riga.prezzo = prezzo;            
						riga.spedizione = spedizione; riga.sconto = sconto;
						riga.spedizione_vera = spedizione_posta; 
						riga.nota = nota;
						riga.fatture = numero_fattura; riga.pagato = pagato;
						riga.spedito = spedito; 
						
						riga.euroiva = 0; riga.pagamento = 0; riga.porto = 0;
						riga.aspetto = 0; riga.colli = 0; riga.peso = 0.0;
						riga.trasporto = ""; riga.data_invio = "";
						
						query.insert(riga); 
						query.execute();
						
						ordini info;        
						vector<Row> cdInseriti = edit;
						vector<int> quantita = cd_collo;
						vector<Row>::iterator itRow; 
						vector<int>::const_iterator itQuantita = quantita.begin();   
						for(itRow = cdInseriti.begin(); itRow != cdInseriti.end(); itRow++)
						{            
						Row r = *itRow;
						info.indice_ordine = indice;
						info.indice_CD = (int)r[0];
						info.codice = (string)r[6];
						info.quantita = *itQuantita;
						if (((int)r[10] == 0) || ((int)r[10] == 1))
						info.prezzo = (float)r[8];
						else     
						info.prezzo = (float)r[9];
						query.insert(info);
						query.execute();
						
						query << "update cd set quantita=quantita-" << (*itQuantita) << ", venduti=venduti+"
						<< (*itQuantita) <<" where indice='" << (int)r[0] << "'";
						query.execute();                
						itQuantita++;
						}
						insert = false;
						}
						}
						
						void Order::FillCombo()
						{   
						SYSTEMTIME time;
						GetLocalTime(&time);
						char b[4];
						string anno = itoa (time.wYear, b, 10);
						string mese = itoa (time.wMonth, b, 10);
						string giorno = itoa (time.wDay, b, 10);
						data = anno + "-" + mese + "-" + giorno;
						
						Query query = c->query();
						query << "select max(fatture) from ordine_riepilogo where year(data) = '" << anno << "'"; 
						Result res = query.store(); 
						Row r = *(res.begin());
						
						if ((string)r[0] == "NULL")
						numero_fattura = 1;
						else
						numero_fattura = (int)r[0]+1; 
						
						HWND hEdit = GetDlgItem(hwndCtl, IDC_COMBO_CLIENT);   
						SendDlgItemMessage(hwndCtl, IDC_COMBO_CLIENT, CB_RESETCONTENT, 0, 0);
						Result::iterator i;
						
						for (i=result.begin(); i != result.end(); i++)
						{
						  r = *i;
						  string linea = (string) r[2] + " " + (string) r[1];
						  SendMessage(hEdit, CB_ADDSTRING, 0, (LPARAM) linea.c_str());
						  }
						  
						  if (!insert)
						  {   
						  
						  hEdit = GetDlgItem(hwndCtl, IDC_COMBO_DATA); 
						  EnableWindow(hEdit, true);
						  hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT); 
						  EnableWindow(hEdit, false);
						  hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT2); 
						  EnableWindow(hEdit, false);
						  hEdit = GetDlgItem(hwndCtl, IDC_REDUCTION); 
						  EnableWindow(hEdit, false);
						  hEdit = GetDlgItem(hwndCtl, IDOK); 
						  EnableWindow(hEdit, true);
						  hEdit = GetDlgItem(hwndCtl, IDC_RADIO_ADR1); 
						  EnableWindow(hEdit, false);
						  hEdit = GetDlgItem(hwndCtl, IDC_RADIO_ADR2); 
						  EnableWindow(hEdit, false);
						  }
						  }
						  
						  void Order::DeleteFromOrder()
						  {
						    HWND lv = GetDlgItem(hwndCtl, IDC_LIST);
						    int indice = SendMessage(lv, LB_GETCURSEL, 0, 0);
						    if(indice != LB_ERR)
						    {
						      Row r = edit[indice];
						      if (((int)r[10] == 0) || ((int)r[10] == 1))
						      {
							prezzo -= (float)r[8];
							prezzo_netto -= (float)r[8];
							}        
							else     
							{    
							prezzo -= (float)r[9];
							prezzo_netto -= (float)r[9];
							}        
							string s;
							char b[10];
							cd_collo[indice] -= 1;
							quantita--;
							if (cd_collo[indice] != 0)
							{
							  s = itoa(cd_collo[indice], b, 10);
							  s = s + " - " + (string)r[1] + " - " + (string)r[2]; 
							  SendMessage(lv, LB_DELETESTRING, indice, 0);
							  SendMessage(lv, LB_INSERTSTRING, indice, (LPARAM) s.c_str());   
							  }      
							  else
							  {   
							  SendMessage(lv, LB_DELETESTRING, indice, 0);
							  edit.erase(edit.begin()+indice);
							  cd_collo.erase(cd_collo.begin()+indice);
							  }    
							  
							  int decimal, segno; 
							  s = _ecvt(prezzo, 6, &decimal, &segno);
							  s.insert(decimal, ".");
							  string s1 = s.substr(0, decimal+3);
							  HWND hEdit = GetDlgItem(hwndCtl, IDC_PRICE); 
							  SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s1.c_str()); 
							  
							  s = itoa(quantita, b, 10);
							  hEdit = GetDlgItem(hwndCtl, IDC_QUANTITY); 
							  SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s.c_str());
							  }
							  }    
							  
							  void Order::InsertInOrder(Row row)
							  {
							    int isOrdered = -10;
							    HWND lv = GetDlgItem(hwndCtl, IDC_LIST);
							    vector<Row>::iterator itRow, selectedRow;
							    char b[10];
							    string s;
							    int indice = 0, i=0;
							    for(itRow = edit.begin(); itRow != edit.end(); itRow++)
							    {   
							    Row r = *itRow;
							    if ((int)r[0] == (int)row[0])
							    {
							      selectedRow = itRow;
							      isOrdered = indice;
							      }    
							      indice++;
							      }
							      
							      if (isOrdered == -10)
							      {
								edit.push_back(row);
								cd_collo.push_back(1);
								s = "1 - " + (string)row[1] + " - " + (string)row[2]; 
								SendMessage(lv, LB_INSERTSTRING, edit.size()-1, (LPARAM) s.c_str());
								
								if (((int)row[10] == 0) || ((int)row[10] == 1))
								{
								  prezzo += (float)row[8];
								  prezzo_netto  += (float)row[8];
								  }    
								  else     
								  {
								    prezzo += (float)row[9];
								    prezzo_netto += (float)row[9];
								    }    
								    quantita++;
								    }    
								    else
								    {
								      cd_collo[isOrdered] += 1;
								      quantita++;
								      Row r = edit[isOrdered];
								      s = itoa(cd_collo[isOrdered], b, 10);
								      s = s + " - " + (string)r[1] + " - " + (string)r[2]; 
								      SendMessage(lv, LB_DELETESTRING, isOrdered, 0);
								      SendMessage(lv, LB_INSERTSTRING, isOrdered, (LPARAM) s.c_str());
								      if (((int)row[10] == 0) || ((int)row[10] == 1))
								      {
									prezzo += (float)row[8];
									prezzo_netto += (float)row[8];
									}    
									else     
									{
									  prezzo += (float)row[9];
									  prezzo_netto += (float)row[9];
									  }    
									  }       
									  
									  int decimal, segno; 
									  s = _ecvt(prezzo, 6, &decimal, &segno);
									  s.insert(decimal, ".");
									  string s1 = s.substr(0, decimal+3);
									  HWND hEdit = GetDlgItem(hwndCtl, IDC_PRICE); 
									  SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s1.c_str()); 
									  s = itoa(quantita, b, 10);
									  hEdit = GetDlgItem(hwndCtl, IDC_QUANTITY); 
									  SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s.c_str());
									  }    
									  
									  BOOL CALLBACK VcDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam)
									  {
									    switch(Message)
									    {
									      case WM_COMMAND:
										switch(LOWORD(wParam))
										{
										  case IDOK:
										    EndDialog(hwnd, IDOK);
										    break;
										    case IDCANCEL:
										      EndDialog(hwnd, IDCANCEL);
										      break;
										      }
										      break;
										      case WM_INITDIALOG:
											vc->hwndCtl = hwnd;
											vc->FillEdit();
											return true;
											default:
											  return false;
											  }
											  return true;
											  }                
											  
											  void Order::OnChangePrice()
											  {
											    TCHAR* passwd;
											    HWND hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT);   
											    int nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
											    if (nLen == 0)
											    spedizione = 0.0;
											    else
											    {         
											    passwd = new TCHAR[nLen+1]; 
											    GetWindowText(hEdit, passwd, nLen+1);
											    spedizione = atof(passwd);
											    }
											    
											    hEdit = GetDlgItem(hwndCtl, IDC_REDUCTION);   
											    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
											    if (nLen == 0)
											    sconto = 0.0;
											    else
											    {         
											    passwd = new TCHAR[nLen+1]; 
											    GetWindowText(hEdit, passwd, nLen+1);
											    sconto = atof(passwd);
											    }
											    
											    hEdit = GetDlgItem(hwndCtl, IDC_SHIPPMENT2);
											    nLen = SendMessage(hEdit, WM_GETTEXTLENGTH, 0, 0);
											    if (nLen == 0)
											    spedizione_posta= 0.0;
											    else
											    {         
											    passwd = new TCHAR[nLen+1]; 
											    GetWindowText(hEdit, passwd, nLen+1);
											    spedizione_posta = atof(passwd);
											    }
											    
											    prezzo = prezzo_netto + spedizione - spedizione_posta - sconto;
											    int decimal, segno; 
											    string s = _ecvt(prezzo, 6, &decimal, &segno);
											    s.insert(decimal, ".");
											    string s1 = s.substr(0, decimal+3);
											    hEdit = GetDlgItem(hwndCtl, IDC_PRICE); 
											    SendMessage(hEdit, WM_SETTEXT, 0, (LPARAM) s1.c_str()); 
											    }
											    
											    
    vector<int> cd_collo;
    string data;
    string nota;
    int ordine;
    int indirizzo;
    int quantita;
    float prezzo;
    float prezzo_netto;
    float sconto;
    float spedizione;
    int cliente;
    bool insert;
    bool pagato;
    bool spedito;
    int numero_fattura;
    float spedizione_posta;
    int tipo_pagamento;
    