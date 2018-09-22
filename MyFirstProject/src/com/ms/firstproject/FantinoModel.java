package com.ms.firstproject;

import java.util.ArrayList;
import java.util.List;

public class FantinoModel {

	private String fantino;
	private String nome;
	private String nascita;
	private String citta;
	private String note;
	private List<String> date;
	private List<String> contrade;
	private List<String> cavalli;
	
	public FantinoModel() {
		date = new ArrayList<String>();
		contrade = new ArrayList<String>();
		cavalli = new ArrayList<String>();
	}
	
	public List<String> getDate() {
			return date;
	}
	
	public void setDate(List<String> c) {
		this.date = c;
	}
	
	public List<String> getContrade() {
		return contrade;
	}

	public void setContrade(List<String> c) {
		this.contrade = c;
	}

	public List<String> getCavalli() {
		return cavalli;
	}

	public void setCavalli(List<String> c) {
		this.cavalli = c;
	}

	public String getFantino() {
		return fantino;
	}

	public void setFantino(String c) {
		this.fantino = c;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String c) {
		this.nome = c;
	}

	public String getNascita() {
		return nascita;
	}

	public void setNascita(String c) {
		this.nascita = c;
	}

	public String getNote() {
		return note;
	}

	public void setNote(String c) {
		this.note = c;
	}

	public String getCitta() {
		return citta;
	}

	public void setCitta(String c) {
		this.citta = c;
	}

	// Will be used by the ArrayAdapter in the ListView
	@Override
	public String toString() {
		return fantino;
	}
}