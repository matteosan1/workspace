package com.ms.dbpalio.masgalano;

import com.ms.dbpalio.dbHandler;

import android.database.Cursor;
import android.database.SQLException;
import android.database.sqlite.SQLiteDatabase;

public class MasgalaniDataSource {
	
	// Database fields
	private SQLiteDatabase database;
	private dbHandler db;
	
	public MasgalaniDataSource(dbHandler dbTemp) {
		db = dbTemp;
	}

	public void open() throws SQLException {
		database = db.getReadableDatabase();
	}

	public void close() {
		db.close();
	}

	public MasgalanoModel getMasgalano(int indice) {
		MasgalanoModel f = new MasgalanoModel();
		String q = "select * from masgalani where _id = " + Integer.toString(indice) +";";
		Cursor cursor =  database.rawQuery(q, null);
		cursor.moveToFirst();
		
		f.indice = indice;
		f.contrada = cursor.getString(1);
		f.organizzatore = cursor.getString(3);
		f.scultore = cursor.getString(4);
		f.data = cursor.getString(2);
		f.dedica = cursor.getString(5);
		f.punteggio = cursor.getString(6);
		f.note = cursor.getString(7);
		
		return f;
	}
	
	public Cursor getMasgalani() {
		String q = "select * from masgalani;";
		Cursor cursor = database.rawQuery(q, null);
		cursor.moveToFirst();
		return cursor;
	}
}
