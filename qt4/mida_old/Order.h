#ifndef ORDER
#define ORDER

#include <windows.h>
#include "mysql++.h"
#include "commctrl.h"
#include <string>
#include <vector>

using namespace mysqlpp;
using namespace std;

class Order
{
    public:
        Order(Connection* con, bool h);
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
                    
    private:
        PROPSHEETPAGE* ps;
        Result result;
        Result result2;
        Row row_temp;
        Connection* c;
        vector<Row> edit;
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
}; 
#endif
