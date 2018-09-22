package com.ms.dbpalio.cavallo;

import java.util.ArrayList;
import java.util.List;

import com.ms.dbpalio.dbHandler;

import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

public class CavalliDataSource {
	
	// Database fields
	private SQLiteDatabase database;
	private dbHandler db;
	
	private List<String> date;
	private List<String> contrade; 
	private List<String> fantini;
	
	public CavalliDataSource(dbHandler dbTemp) {
		db = dbTemp;
		date = new ArrayList<String>(); 
		contrade = new ArrayList<String>();
		fantini = new ArrayList<String>();
	}

	public void open() throws SQLException {
		database = db.getReadableDatabase();
	}

	public void close() {
		db.close();
	}

	public CavalloModel getCavallo(String nome) {
		String[] c = new String[] {"Aquila", "Bruco", "Chiocciola", "Civetta",
			"Drago", "Giraffa", "Istrice", "Leocorno", "Lupa", "Nicchio",
			"Oca", "Onda", "Pantera", "Selva", "Tartuca", "Torre", "Montone"};
		//Log.v("1", nome);
		date.clear();
		contrade.clear();
		fantini.clear();
		
		String q2 = "select vittorie.data,contrada,fantino, (vittorie.primo=mosse.contrada) from mosse,vittorie " +
				"where cavallo = \"" + nome + "\" and vittorie.indice = mosse.indice;";
		
		Cursor cursor2 = database.rawQuery(q2, null);
		cursor2.moveToFirst();
        while (cursor2.isAfterLast() == false) {
        	date.add(cursor2.getString(0));
        	
        	if (cursor2.getInt(3) == 1)
        		contrade.add(c[cursor2.getInt(1)].toUpperCase());
        	else
        		contrade.add(c[cursor2.getInt(1)]);
        	fantini.add(cursor2.getString(2));
       	    cursor2.moveToNext();
        }
        cursor2.close();
        CavalloModel f = new CavalloModel();
        f.setNome(nome);
        f.setFantini(fantini);
        f.setDate(date);
        f.setContrade(contrade);
        
		return f;
	}
	
	public List<CavalloModel> getAllCavalli() {
		List<CavalloModel> cavalli = new ArrayList<CavalloModel>();
		String q = "select distinct cavallo from mosse where cavallo != \"\";";
		Cursor cursor = database.rawQuery(q, null);
		cursor.moveToFirst();
		while (!cursor.isAfterLast()) {
			CavalloModel f = cursorToComment(cursor);
			cavalli.add(f);
			cursor.moveToNext();
		}
		
		// Make sure to close the cursor
		cursor.close();
		return cavalli;
	}

	private CavalloModel cursorToComment(Cursor cursor) {
		CavalloModel f = new CavalloModel();
		f.setNome(cursor.getString(0));
		
		return f;
	}
		
	/*
	public FantinoModel createFantino(String fantino) {
		ContentValues values = new ContentValues();
		values.put("fantino", fantino);
		
		// To show how to query
		Cursor cursor = database.query("fantini", allColumns, null, null, null, null, null);
		cursor.moveToFirst();
		return cursorToComment(cursor);
	}

	public void deleteFantino(FantinoModel fantino) {
		System.out.println("Comment deleted with id: ");
		//database.delete("fantini", MySQLiteHelper.COLUMN_ID+ " = " + id, null);
	}
	*/

}
