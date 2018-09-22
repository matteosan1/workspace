#include <windows.h>
#include "mysql++.h"
#include "commctrl.h"

#include <string>
#include <vector>

using namespace mysqlpp;
using namespace std;

class PSheet
{
    public:
        PSheet(Connection* con, bool h);
        virtual ~PSheet();
        /*
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
        string GetData() { return data; };
        string GetNota() { return nota; };
        */                     
        void FillCombo();
        void InsertInOrder(Row row);
        void DeleteFromOrder();
        void OnOrdExit();
        void OnDelExit();
        void SaveInfo();
        void OnSearchOrders();
        void OnFillOrder();
        void OnChangePrice();
        BOOL OnPrint();
        void InitDialog();
        void PrintAddress();
        void PrintTable(bool);
        void PrintInitTable();
        void PrintEndTable(bool);
        void PrintHeader();
        void PrintLabel();
        
        BOOL CALLBACK OrdDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
        BOOL CALLBACK DelDlgProc(HWND hwnd,UINT Message,WPARAM wParam,LPARAM lParam);
        HWND hwndCtl2;
        HWND hwndCtl;
        
                    
    private:
        HFONT hfontStd1, hfontBold1, hfontStd2, hfontBold2, hfontSmall;
        int iLine, yChar, wChar;
        PRINTDLG pd;
        float totale_imponibile, sconto_finale, totale_finale;
        
        string combo[10][10];
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
        float iva;
        float sconto;
        float spedizione;
        int cliente;
        bool insert;
        bool pagato;
        bool spedito;
        int numero_fattura;
        float spedizione_posta;
        int tipo_pagamento;
        
        int vat;
        int metodo;
        int porto;
        int shape;
        int colli;
        float peso;
        string carrier;
        string data_spedizione;
}; 


