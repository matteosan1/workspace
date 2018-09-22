 
<html>
<head>
<meta http-equiv="Content-Language" content="it">
<meta name="description" content="Pianeta Fantacalcio.it ... Voti fantacalcio, utility per il calcolo dei voti e l'amministrazione di squadre, statistiche dei giocatori con Quotazioni, voti gazzetta dello sport, giornali fantacalcistici, calcio, fantacalcio, sport, calcio, gioco, serie a, squalificati, indisponibili, pagelle">
<meta name="robots" content="index,follow">
<meta name="keywords" content="Campionato online, Lega Aretusa, Fantapresidenti, Statistiche, Calcio, voti gazzetta dello sport, voti corriere dello sport, giornali fantacalcistici, calcio, fantacalcio, sport, calcio, gioco, serie a, squalificati, indisponibili, pagelle">
<META NAME="rating" CONTENT="General">
<META NAME="MS.LOCALE" CONTENT="IT"> 
<META NAME="CATEGORY" CONTENT="home page"> 
<META http-equiv="Classification" CONTENT="voti gazzetta"> 
<META NAME="URL" CONTENT="http://www.pianetafantacalcio.it"> 
<META NAME="revisit-after" CONTENT="31 days"> 
<meta name="Author" content="PianetaFantaCalcio.it (info@pianetaFantacalcio.it)">
<meta name="Language" content="IT">
<meta http-equiv="imagetoolbar" content="no">
<meta http-equiv="imagetoolbar" content="false">
<META NAME="VW96.objecttype" CONTENT="voti gazzetta dello sport, voti corriere dello sport,  giornali fantacalcistici, calcio, fantacalcio, fantagazzetta, sport, calcio, gioco, serie a, squalificati, indisponibili, pagelle">
<META NAME="DC.Title" CONTENT="voti gazzetta dello sport, voti corriere dello sport,  giornali fantacalcistici, calcio, fantacalcio, fantagazzetta, sport, calcio, gioco, serie a, squalificati, indisponibili, pagelle"> 
<META NAME="DC.Subject" CONTENT="voti gazzetta dello sport, voti corriere dello sport, giornali fantacalcistici, calcio, fantacalcio, fantagazzetta, sport, calcio, gioco, serie a, squalificati, indisponibili, pagelle">
<META NAME="DC.Description" CONTENT="voti gazzetta dello sport, voti corriere dello sport, giornali fantacalcistici, calcio, fantacalcio, fantagazzetta, sport, calcio, gioco, serie a, squalificati, indisponibili, pagelle">
<META NAME="DC.Coverage.PlaceName" CONTENT="Global"> 
<meta http-equiv="Content-Type" content="text/html; charset=iso-8859-1" />



<link href="pianetafanta.css" rel="stylesheet" media="screen">
<link href="stampante.css" rel="stylesheet" media="print">
<link href="favicon.ico" rel="SHORTCUT ICON">
<script language="JavaScript">

//funzione che determina la posizione del mouse
var isMinNS4 = (document.layers) ? 1 : 0;
var isMinIE4 = (document.all) ? 1 : 0;
var mouseX = 0;
var mouseY = 0;
if (isMinNS4){document.captureEvents(Event.MOUSEMOVE);}

document.onmousemove = getMousePosition;



function clearPreloadPage() { //DOM
	if (document.getElementById){
			document.getElementById('prepage').style.visibility='hidden';
	}
	else {
		if (document.layers){ //NS4
				document.prepage.visibility = 'hidden';
		}
		 else { //IE4
				document.all.prepage.style.visibility = 'hidden';
		}
	}
}

function Loading() { 
//document.write('<div id="prepage" style="position: absolute;top: 50%; left: 50%; width: 32px; height: 32px; margin-left: -16px; margin-top: -16px;"><img src="Images/Loading.gif"></div>')
document.write('<div id="prepage"  style="position: absolute;top: 50%; left: 50%; width: 32px; height: 32px; margin-left: -16px; margin-top: -16px;border: 3px solid #0000FF" bgcolor="#BBDDFF"><table border="0" width="250" cellpadding="2" cellspacing="0"><tr><td bgcolor="#BBDDFF"><p align="center"><img src="Images/Loading.gif"><td width="193" bgcolor="#BBDDFF"><b><font face="Verdana" size="2">Attendere.<br>Caricamento in corso</font></b></td></tr></table></div>')
}

// -----------------------------------------------------------------------------------------------------------
	function getMousePosition(e){
		if (isMinNS4){
			mouseX = e.pageX+100;
			mouseY = e.pageY+20;
		}

		if (isMinIE4){
			mouseX = event.clientX + document.body.scrollLeft;
			mouseY = event.clientY + document.body.scrollTop;
		}else{
			mouseX = e.pageX+100;	
			mouseY = e.pageY+20;
		}
		return true;
	}


function setta(){
	if (document.formtutto("cookies").checked){
		document.formtutto("salvac").value = 1
	}
}

function twoinone(nr){
	if (nr==1){
		parent.superiore.location.href="menu.asp"
		parent.inferiore.location.href="vetrina.asp"
	}
}

function sicuro(){ 
   flag = confirm('Sei Sicuro di voler cliccare?'); 
   if (flag==true) {
	 return true; 
   } 
   else {
	 return false;
   } 
}



var default1 = "PianetaFantaCalcio.it - Il portale dei Fantapresidenti -"
var text1 = "PianetaFantaCalcio.it - Risultati, Classifiche, Rubriche, Statistiche, Curiosità";
var text2 = "PianetaFantaCalcio.it - Voti sempre aggiornati ...i primi d'Italia!!!";
var text3 = "PianetaFantaCalcio.it....ogni giorno una sorpresa per te.";
var changeRate = 5000; // 1000 = 1 second
var messageNumber = 0;

function changeStatus() {
  if (messageNumber == 0) {
     document.title=default1;
    }
  else if (messageNumber == 1) {
     document.title=text1;
    }
  else if (messageNumber == 2) {
     document.title=text2;
     }
  else if (messageNumber == 3) {
     document.title=text3;
     messageNumber = 0;
     }
  messageNumber++;
  setTimeout("changeStatus();",changeRate);
}
changeStatus(); // leave here to run right away





// infortunati
function CalcolaInf(obj,Tipo){
		if (obj.value==''){
		
		}else{
			Lungh		= obj.value.length;
			MyPos1		= obj.value.indexOf("|");
		 	MyPos2		= obj.value.indexOf("|",MyPos1+1);	
			Qta_flag	= MyPos2-1 - MyPos1;
			
			Nome		= obj.value.substr(0,MyPos1);
			Squadra		= obj.value.substr(MyPos1+1,Qta_flag);
			Ruolo		= obj.value.substr(MyPos2+1,Lungh);
			if (Tipo==1){
				document.formtutto.nome1.value = Nome
				document.formtutto.squadra1.value = Squadra
				document.formtutto.ruolo1.value = Ruolo
			}
			if (Tipo==2){
				document.formtutto.nome2.value = Nome
				document.formtutto.squadra2.value = Squadra
				document.formtutto.ruolo2.value = Ruolo
			}
			if (Tipo==3){
				document.formtutto.nome3.value = Nome
				document.formtutto.squadra3.value = Squadra
				document.formtutto.ruolo3.value = Ruolo
			}
			if (Tipo==4){
				document.formtutto.nome4.value = Nome
				document.formtutto.squadra4.value = Squadra
				document.formtutto.ruolo4.value = Ruolo
			}
			if (Tipo==5){
				document.formtutto.nome5.value = Nome
				document.formtutto.squadra5.value = Squadra
				document.formtutto.ruolo5.value = Ruolo
			}
			if (Tipo==6){
				document.formtutto.nome6.value = Nome
				document.formtutto.squadra6.value = Squadra
				document.formtutto.ruolo6.value = Ruolo
			}			
			if (Tipo==7){
				document.formtutto.nome7.value = Nome
				document.formtutto.squadra7.value = Squadra
				document.formtutto.ruolo7.value = Ruolo
			}
			if (Tipo==8){
				document.formtutto.nome8.value = Nome
				document.formtutto.squadra8.value = Squadra
				document.formtutto.ruolo8.value = Ruolo
			}
			
			if (Tipo==9){
				document.formtutto.nome9.value = Nome
				document.formtutto.squadra9.value = Squadra
				document.formtutto.ruolo9.value = Ruolo
			}
			
			if (Tipo==10){
				document.formtutto.nome10.value = Nome
				document.formtutto.squadra10.value = Squadra
				document.formtutto.ruolo10.value = Ruolo
			}
			if (Tipo==11){
				document.formtutto.nome11.value = Nome
				document.formtutto.squadra11.value = Squadra
				document.formtutto.ruolo11.value = Ruolo
			}
			if (Tipo==12){
				document.formtutto.nome12.value = Nome
				document.formtutto.squadra12.value = Squadra
				document.formtutto.ruolo12.value = Ruolo
			}
			if (Tipo==13){
				document.formtutto.nome13.value = Nome
				document.formtutto.squadra13.value = Squadra
				document.formtutto.ruolo13.value = Ruolo
			}
			if (Tipo==14){
				document.formtutto.nome14.value = Nome
				document.formtutto.squadra14.value = Squadra
				document.formtutto.ruolo14.value = Ruolo
			}
			if (Tipo==15){
				document.formtutto.nome15.value = Nome
				document.formtutto.squadra15.value = Squadra
				document.formtutto.ruolo15.value = Ruolo
			}			
			



		}
}



function validate(){

	var bene=true;

  	if (document.formreg.email.value.indexOf("@") == -1) {
		alert("E' necessario inserire un indirizzo E-Mail valido.")
		bene=false;
		document.formreg.email.focus();
		return false;
	}	

	if (document.formreg.email.value.indexOf(".") == -1) {
		alert("E' necessario inserire un indirizzo E-Mail valido.")
		bene=false;
		document.formreg.email.focus();
		return false;
	}	
	
	if (!document.formreg.valuemail.checked) {
	    bene=false;
	    alert("Attenzione senza il consenso al trattamento dei dati non è possibile usufruire del servizio.");
	    return (false);
	}

	var reg1 = /(@.*@)|(\.\.)|(@\.)|(\.@)|(^\.)/; // not valid
	var reg2 = /^.+\@(\[?)[a-zA-Z0-9\-\.]+\.([a-zA-Z]{2,3}|[0-9]{1,3})(\]?)$/; // valid
	if (!reg1.test(document.formreg.email.value) && reg2.test(document.formreg.email.value)) { // if syntax is valid
		document.valuemailform.uemail.value = document.formreg.email.value
		// lo messo da codice
		//alert(document.valuemailform.uemail.value)
		//http://www.valuemail.it/online_reg/affirmation.jsp
       	document.valuemailform.submit()
       	win = window.open("","win","width=600,height=750,toolbar=0,scrollbars=1");

	} else{
		alert("E' necessario inserire un indirizzo E-Mail valido.")
		return false;
	}        
  	
  	if (bene) {return (true);}
}


function popupHelp(status,titolo,messaggio){
		if(status=='show'){
			newdiv = document.createElement("div");
			newdiv.id = "mine";
			document.body.appendChild(newdiv);
			mydiv = document.getElementById("mine");
			newdiv.style.position = "absolute";
			//newdiv.style.zindex= "25";
			newdiv.style.left = mouseX;
			newdiv.style.top = mouseY;
			var content="<table class='HelpQuota' width='250' border='0' cellpadding='1' cellspacing='0'>"
			    content = content + "<tr><td colspan='4' align='center'> " +  titolo
			    content = content + "<tr><td  align='justify'> " + messaggio + "</td>"
			    content = content + "</table>";
			    newdiv.innerHTML=""+content;
		}else{
			    newdiv.innerHTML="";
		}
}


</script>





</head>
<body onLoad="clearPreloadPage();populate()" bgcolor="#9397D0" topmargin="0" leftmargin="0">
<script type="text/javascript" language="JavaScript">Loading();</script>

<div align="center"  Id="avviso">
<script type="text/javascript">
var uri = 'http://impit.tradedoubler.com/imp?type(js)g(16565838)a(934430)' + new String (Math.random()).substring (2, 11);
document.write('<sc'+'ript type="text/javascript" src="'+uri+'" charset="ISO-8859-1"></sc'+'ript>');
</script> 
<TABLE cellSpacing=0 cellPadding=0 width=765 border=0 bordercolor="#111111">
   <TR>
    <TD style="border-left-style: solid; border-left-width: 1; border-right-style: solid; border-right-width: 1; border-top-style: solid; border-top-width: 1">
        <table align="center" border="0" cellpadding="0" cellspacing="0" width="765">
          <tr>
            <td class="Sfondo_sopra" rowspan="5" valign="middle" align="center">	
			<img border="0" src="images/logonew2007.gif" width="138" height="107">
            </td>
            <td valign="top"  height="19" class="Sfondo_sopra" align="right">

			<table align="right" cellpadding="0" cellspacing="0"  >
				<tr>
					<td>
					<a href="pubblicita.asp" target="_blank">Vuoi fare pubblicità in questo sito? &nbsp;</a>
					</td>
					<td>
					&nbsp;<a href="collabora.asp" target="_blank">Collabora con noi</a>
					</td>

				</tr>
			</table>

		</tr>
          <tr>
            <td valign="top"  height="51" class="Sfondo_sopra" align="center"><br>
            <script type="text/javascript" language="JavaScript" src="http://adv08.edintorni.net/affiliati/content/468x60/?q=ACMS_CRAWLER&a=2773&s=ffffff&b=000000&t=993300&d=000000&u=990000"></script><br>
				</tr>
          <tr>
            <td valign="middle" class="Sfondo_sopra" width="620" align="left">
				&nbsp;
				<TABLE cellSpacing=0 cellPadding=0 width=620 bgColor=#5f5f7f border=0>
        		<TBODY>
        		<TR>
		          <TD align=left width=18 rowSpan=2 valign="top" >
					<IMG height=18 src="images/menu/gesq.gif" ></TD>
		          <TD bgColor=white><IMG height=1 src="images/menu/t.gif" width=1></TD>
		        </TR>

		        <TR>
		          <TD align="left" height="33">
              
		<script type="text/javascript" src="milonic_src.js"></script>	
		<script type="text/javascript">
			if(ns4)_d.write("<scr"+"ipt type=text/javascript src=mmenuns4.js><\/scr"+"ipt>");		
			  else _d.write("<scr"+"ipt type=text/javascript src=mmenudom.js><\/scr"+"ipt>"); 
		</script>
	
	<script type="text/javascript" src="menu_dataBanner15.js"></script>

<a href="http://www.milonic.com/beginner.php">
<font color="#5F5F7F">http://www.milonic.com/beginner.php</font></a><font color="#5F5F7F">



		                	&nbsp;</font></TD>

		        </TR>
		        </TBODY>
		        </TABLE>
		  </tr>
		  <tr>
            <td valign="middle" class="Sfondo_sopra" width="630" align="center">
</tr>
		  </table>
		  <script language="javascript">
var uri = 'http://impit.tradedoubler.com/imp/js/16357060/934430?' + new String (Math.random()).substring (2, 11);
document.write('<sc'+'ript language="JavaScript" src="'+uri+'" charset="ISO-8859-1"></sc'+'ript>');
</script>

    </TD></TR>
</TABLE>
</div>

<div align="center">
<TABLE cellSpacing=0 cellPadding=0 width=765 border=0 style="border-collapse: collapse" bordercolor="#111111">
  <TBODY>
  <TR>
    <TD width=1 bgColor=#000000>
	    <IMG alt="" src="spacer.gif" border=0 width="1" height="1">
    </TD>
    <td valign="top" width="10" height="100%" class="Sfondo_sx">
			

			    <TD vAlign=top width=615 bgcolor="#FFFFFF">
	    		<p align="center"><br><a href='http://www.payclick.it/affiliate/scripts/t.php?a_aid=d24dab18&amp;a_bid=b8bf2e45'><img src='http://www.payclick.it/affiliate/scripts/sb.php?a_aid=d24dab18&amp;a_bid=b8bf2e45' border="0" alt="" title=""></a></p><br>
	    					
<script Language='JavaScript' src='http://www.spotmania.it/adv/popunder.asp?idx=957'></script>
<div align="center">
<br>
<img border="0" src="images/menu/Intesta_TabellaVotiUfficiali1.gif" align="left"><br><br>
 <span class="testo1_corpo11_bold_blu">
<br>
 <table  width="300" border="0" cellspacing="0" cellpadding="0" height="14" align=center>
	          <tr><td   colspan="2"background="images/sopra_tabella.gif">
						<font size="1" color="#FFFFFF" face="Verdana">&nbsp;&nbsp; 
						</font></td>
					<td colspan="9" background="images/sopra_tabelladx.gif" height="14" width="161">
						<font size="1">&nbsp;</font></td>
				</tr>
          </table>  
   <table valign="top" border="0" bgcolor="#f2f2f2" cellpadding="0" width="300" cellspacing="0" style="border-left: 1px solid #C0C0C0; border-right: 1px solid #C0C0C0; border-bottom: 1px solid #C0C0C0; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px">
		<tr>
    		<td COLSPAN="3" align="center" valign="top" class="p_dx" >
    	    <span class="arialbianco11grass">4° Giornata</span>
      	<tr> 
           	<td align="center" width="50" ></td>
			<td align="center" width="50" ></td>
            <td  align="center" width="50"></td>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Fiorentina.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Fiorentina">Fiorentina</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Atalanta.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Atalanta">Atalanta</a>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Genoa.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Genoa">Genoa</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Livorno.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Livorno">Livorno</a>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Inter.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Inter">Inter</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Catania.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Catania">Catania</a>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Juventus.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Juventus">Juventus</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Udinese.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Udinese">Udinese</a>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Lazio.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Lazio">Lazio</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Empoli.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Empoli">Empoli</a>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Napoli.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Napoli">Napoli</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Sampdoria.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Sampdoria">Sampdoria</a>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Palermo.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Palermo">Palermo</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Torino.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Torino">Torino</a>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Parma.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Parma">Parma</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Cagliari.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Cagliari">Cagliari</a>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Reggina.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Reggina">Reggina</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Roma.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Roma">Roma</a>
	  	        <tr onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''"> 
                 	<td align="left"  class="sotto"><img src="images/maglie/Siena.gif" border="0">
                       	<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Siena">Siena</a>
                    <td align="center"  class="sotto">- 
					<td align="left" class="sotto"><img src="images/maglie/Milan.gif" border="0">
						<a class="VociSquadre" href="Voti_Ufficiali.asp?tipolink=2&amp;squadra=Milan">Milan</a>
 	</table>

	
	<font face="Verdana" size="4"><a href="Voti_UfficialiTutti.asp">Visualizza Tutti<br></a></font>
    <script type="text/javascript"><!--
google_ad_client = "pub-5071569578801416";
google_ad_width = 234;
google_ad_height = 60;
google_ad_format = "234x60_as";
google_ad_type = "text";
//2006-09-25: voti
google_ad_channel ="3901196311";
google_color_border = "FFFFFF";
google_color_bg = "FFFFFF";
google_color_link = "0000FF";
google_color_text = "000000";
google_color_url = "000000";
//--></script>
<script type="text/javascript"
  src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
</script><br>
    <font size="2"><a class="notizie8nero" href="vetrina.asp">Torna Indietro</a></font>
</div>

				


	<p align="center">
	
<p align="center"><br><script type=text/javascript><!--
google_ad_client = "pub-5071569578801416";
google_ad_width = 468;
google_ad_height = 60;
google_ad_format = "468x60_as";
google_ad_channel ="";
//--></script><script type=text/javascript
src=http://pagead2.googlesyndication.com/pagead/show_ads.js>
</script></p><br>
	<TD vAlign=top align=right width=130 height="100%">

	<div Id="avviso">
<TABLE   height="100%" class=Sfondo_dx valign=top cellSpacing=0 cellPadding=0 width=130 border=0 style="border-right: 1px solid #000000"  >

<!-- SPONSOR -->
<TR>
    	<td width="125" valign="top"><br>
    	<IMG height=10 src="images/menu/t.gif" width=1>
			 <TABLE id=MEN cellSpacing=0 cellPadding=0 width=120 align=center border=0 bgColor=#ffffff >
			  <TBODY><TR><TD>
			      <TABLE cellSpacing=0 cellPadding=0 width=120 border=0>
			        <TBODY>
			        <TR>
			        
			          <TD width=1 bgColor=#ffffff rowSpan=2>
						<IMG height=1 Src="images/menu/t.gif" width=1></TD>
			          <TD class=TitoloMenu width=108>&nbsp; SPONSOR</TD>
			        </TR>
			        <TR>
			          <TD class=D width=108>
			          <table border="0" style="border-collapse: collapse; border: 1px solid #990033; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px" id="table1">
						<tr>	
							<td  onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''" 
								 style="border: 1px solid #990033; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px">
							<script type="text/javascript" language="JavaScript" src="http://adv08.edintorni.net/affiliati/content/120x120/?q=ACMS_CRAWLER&a=2773&s=000000&b=&t=FF6600&d=FFFFFF&u=0000CC"></script>
							</td>
						</tr>
						<tr>
							<td onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''" style="border: 1px solid #990033; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px">
								<script Language='JavaScript' src='http://www.spotmania.it/adv/120x60.asp?idx=957'></script></td>
						</tr>
						
						<tr>
							<td onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''" style="border: 1px solid #990033; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px">
								<!-- INIZIO del codice HTML di zanox-affiliato -->
 <!--(Il codice HTML non deve essere modificato per garantire la assoluta funzionalità)-->
<a href="http://ad.zanox.com/ppc/?2780490C978100842T"><img src="http://ad.zanox.com/ppv/?2780490C978100842" align="bottom" width="120" height="120" border="0" hspace="1" alt="soscartucce 120x120"></a>
<!-- FINE del codice HTML fi zanox affiliato -->
</td>
						</tr>
<tr>
							<td onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''" style="border: 1px solid #990033; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px">
								<a href='http://www.payclick.it/affiliate/scripts/t.php?a_aid=d24dab18&amp;a_bid=0ea4db8c'><img src='http://www.payclick.it/affiliate/scripts/sb.php?a_aid=d24dab18&amp;a_bid=0ea4db8c' border="0" alt="" title=""></a></td>
						</tr>
<tr>
							<td onmouseover="style.backgroundColor='#F0A500'" onmouseout="style.backgroundColor=''" style="border: 1px solid #990033; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px">
								<a href="http://www2.bet-at-home.com/affiliate.aspx?aid=13195" target="blank">
<img src="images/banner/120x60_it_boxen.gif"></a></td>
						</tr>

					</table>
					  </TD>
				    </TR>
			        </TBODY>
			        </TABLE>
			</TD></TR></TBODY></TABLE>
			
					

<!-- Area Riservata Lega Aretusa-->



<!-- Area Riservata -->

<form method="POST" action="vetrina.asp" name="formtutto" id="formtutto" class="castesto"> 
<TR>
    	<td width="100%" valign="top">
    	<IMG height=10 src="images/menu/t.gif" width=1>
			 <TABLE id=MEN cellSpacing=0 cellPadding=0 width=120 align=center border=0>
			  <TBODY><TR><TD>
			      <TABLE cellSpacing=0 cellPadding=0 width=120 border=0>
			        <TBODY>
			        
			             	          
			         <TR>
			          <TD width=1 bgColor=#ffffff rowSpan=2>
						<IMG height=1 Src="images/menu/t.gif" width=1></TD>
			          <TD class=TitoloMenu  width=108>&nbsp;&nbsp; LOGIN</TD>
			        </TR>
			        <TR>
			          <TD class=D width=108>
			          <table border="0" style="border-style:solid; border-width:1px; border-collapse: collapse; padding-left: 4px; padding-right: 4px; padding-top: 1px; padding-bottom: 1px" id="table1" width="113" cellpadding="0" bordercolor="#000000">
						<tr>	
							<td class="sfondo_ocra" >
							<p align="center"><font face="Verdana" size="2">UserID</font><br>
	            	    	<input type="text" name="userid" size="10"  style="border-style: solid; border-width: 1px"><tr>	
							<td class="sfondo_ocra">
							<p align="center"><font face="Verdana" size="2">Password</font><br>
   			                 <input type="password" name="password" size="10" style="border-style: solid; border-width: 1px">
							</td>
						</tr>
						<TR>
						<td class="sfondo_ocra" align="center">	
							<script type="text/javascript"><!--
google_ad_client = "pub-5071569578801416";
google_ad_width = 125;
google_ad_height = 125;
google_ad_format = "125x125_as";
google_ad_type = "text";
//2006-09-25: login
google_ad_channel ="7050338941";
google_color_border = "F0A500";
google_color_bg = "F0A500";
google_color_link = "000000";
google_color_text = "000000";
google_color_url = "000000";
//--></script>
<script type="text/javascript"
  src="http://pagead2.googlesyndication.com/pagead/show_ads.js">
</script><br>
							<input type="image" src="images/buttonok.gif" name="ok" id="ok" alt="Entra Area Riservata"> &nbsp;
      					 </td>
						</TR>
						<TR>
						<td class="sfondo_ocra"  align="center">	
	
	              	    <a class="VociMenu3" href="Visualizza_PwdSmarrita.asp">
						Password persa?</a>
							
						<a class="VociMenu3" href="LegaAretusa_registrazione.asp?tipolink=1">
						Gioca Online GRATIS</a></td>
						</TR>
						<tr>
      		                 <td align="center" class="sfondo_ocra" > 
             		          <img border="0" src="images/regolamentofanta.gif"><br>
								<a class="VociMenu3"  title="Tra poco online" href="LegaAretusa_RegolamentoOnLine.asp">	Regolamento 
								Online	2007\2008</a><br>
&nbsp;</td>
                    		   </tr>
						<TR>
						<td class="sfondo_ocra"  align="center">	
	
	              	    &nbsp;</td>
						</TR>
						</table>
					  </TD>
				    </TR>
  	        		<input type="hidden" name="salvac" value="0">
			    	
			        </TBODY>
			        </TABLE>
			</TD></TR></TBODY></TABLE></form>






<!-- Premio Fedeltà -->

<br>
<!-- area riservata -->		 




<tr>
 <TD  height="100%" width="100%" bgcolor="#FFFFFF">&nbsp;
		 
		 <table border="0" class="Sfondo_bianco" cellpadding="0" cellspacing="0" width="120" height="421" >
         <tr>
          <td ><img src="images/spacer.gif">&nbsp;</td>
          </tr>
          </table>

 </TD></tr>
</TABLE>
	</TD>
	</TR>
	</TBODY></TABLE>
</div>
<div Id="avviso" align="center">
<TABLE cellSpacing=0 cellPadding=0 width=765 align="center" border=0>
  <TBODY>
  <TR>
    <TD>
      <div align="left">
      <TABLE cellSpacing=0 cellPadding=0 width=765 border=0 style="border-collapse: collapse" bordercolor="#000000" bgcolor="#FFFFFF">
        <TR>
          <TD style="border-left-style: solid; border-left-width: 1; border-right-style: solid; border-right-width: 1; border-top-style: solid; border-top-width: 1; padding-left: 4; padding-right: 4; padding-top: 1; padding-bottom: 1">
          <p align="center">
			</TD>
        </TR>
      </TABLE>
      </div>
    </TD>
  </TR>

  <TR>
    <TD>
      <div align="left">
            <TABLE width=765 cellSpacing=0 cellPadding=0 style="padding:0; border-collapse: collapse" bordercolor="#000000" bgcolor="#FFFFFF">
              <TR>
                <TD   class="p_dx"  style="border-left:1px solid #000000; border-right:1px solid #000000; border-bottom:3px solid #000000; " height="25">
                 	<p align="center"><span  class="notizie8nero">© 2003-2007
	                 <a href="mailto:info@pianetafantacalcio.it">PianetaFantacalcio.it</a> - Tutti i diritti riservati - 
                    Tutti i marchi e nomi sono dei legittimi proprietari <br>
                    </span>
                    <font face="arial" size="1"><b>®</b></font><font face="Arial,Helvetica" size="1"> 
                    Fantacalcio è un marchio registrato da </font>
                    <font color="#ffffff"><a href="http://www.fantacalcio.it">
                    <font face="Arial" size="1" color="#000000">Studio Vit srl</font></a></font>
                   		</TD></TR>
            </TABLE>
      </div>
    </TD>
  </TR>
 
</TBODY>
</TABLE>
</div><br>
</html>