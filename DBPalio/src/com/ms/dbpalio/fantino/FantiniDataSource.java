package com.ms.dbpalio.fantino;

import java.util.ArrayList;
import java.util.List;

import com.ms.dbpalio.dbHandler;

import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

public class FantiniDataSource {
	
	// Database fields
	private SQLiteDatabase database;
	private dbHandler db;
	
	private List<String> date;
	private List<String> contrade; 
	private List<String> cavalli;
	
	public int status = 0;
	
	public FantiniDataSource(dbHandler dbTemp) {
		db = dbTemp;
		date = new ArrayList<String>(); 
		contrade = new ArrayList<String>();
		cavalli = new ArrayList<String>();
	}

	public void open() throws SQLException {
		database = db.getReadableDatabase();
	}

	public void close() {
		db.close();
	}

	public FantinoModel getFantino(String nome) {
		String[] c = new String[] {"Aquila", "Bruco", "Chiocciola", "Civetta",
			"Drago", "Giraffa", "Istrice", "Leocorno", "Lupa", "Nicchio",
			"Oca", "Onda", "Pantera", "Selva", "Tartuca", "Torre", "Montone"};
		
		String q1 = "select * from fantini where fantino = \""+ nome +"\";";
		Cursor cursor = database.rawQuery(q1, null);
		cursor.moveToFirst();
		FantinoModel f = cursorToComment(cursor);
		cursor.close();
		
		date.clear();
		contrade.clear();
		cavalli.clear();
		
		String q2 = "select vittorie.data,contrada,cavallo, (vittorie.primo=mosse.contrada) from mosse,vittorie " +
				"where fantino = \"" + nome + "\" and vittorie.indice = mosse.indice;";
		
		Cursor cursor2 = database.rawQuery(q2, null);
		cursor2.moveToFirst();
        while (cursor2.isAfterLast() == false) {
        	date.add(cursor2.getString(0));
        	if (cursor2.getInt(3) == 1)
        		contrade.add(c[cursor2.getInt(1)].toUpperCase());
        	else
        		contrade.add(c[cursor2.getInt(1)]);
        	cavalli.add(cursor2.getString(2));
       	    cursor2.moveToNext();
        }
        cursor2.close();
        
        f.setCavalli(cavalli);
        f.setDate(date);
        f.setContrade(contrade);
        
		return f;
	}
	
	public List<FantinoModel> getAllFantini() {
		List<FantinoModel> fantini = new ArrayList<FantinoModel>();
		String q = "select * from fantini;";
		Cursor cursor = database.rawQuery(q, null);
		cursor.moveToFirst();
		while (!cursor.isAfterLast()) {
			FantinoModel f = cursorToComment(cursor);
			fantini.add(f);
			cursor.moveToNext();
		}
		
		// Make sure to close the cursor
		cursor.close();
		return fantini;
	}

	private FantinoModel cursorToComment(Cursor cursor) {
		FantinoModel f = new FantinoModel();
		f.setFantino(cursor.getString(0));
		f.setNome(cursor.getString(1));
		f.setNascita(cursor.getString(2));
		f.setCitta(cursor.getString(3));
		f.setNote(cursor.getString(4));

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
