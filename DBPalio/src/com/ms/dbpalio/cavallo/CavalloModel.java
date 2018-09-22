package com.ms.dbpalio.cavallo;

import java.util.ArrayList;
import java.util.List;

public class CavalloModel {

	private String nome;
	private List<String> date;
	private List<String> contrade;
	private List<String> fantini;
	
	public CavalloModel() {
		date = new ArrayList<String>();
		contrade = new ArrayList<String>();
		fantini = new ArrayList<String>();
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

	public List<String> getFantini() {
		return fantini;
	}

	public void setFantini(List<String> c) {
		this.fantini = c;
	}

	public String getNome() {
		return nome;
	}

	public void setNome(String c) {
		this.nome = c;
	}

	// Will be used by the ArrayAdapter in the ListView
	@Override
	public String toString() {
		return nome;
	}
}