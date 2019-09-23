package simtrace_viewer;

import java.io.*;
import java.util.*;
//import javax.swing.*;
import java.lang.Integer;
import java.io.File;
import org.w3c.dom.Document;
import org.w3c.dom.*;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException; 

import simtrace_viewer.Symbol;

public class ParseSymbols {
    String SymbolsFile;
    List<Symbol> symbols = new ArrayList<Symbol>();

    public void ParseSymbols() {
    }

    public void Dump() {
        System.out.println("Symbols file: '" + SymbolsFile + "'");

        for (Symbol s : symbols) {
	    s.Dump();
	}
    }

    public Symbol Match(long address) {
        Symbol ns = new Symbol();

        for (Symbol s : symbols) {
	    if (s.Match(address)) { 
		ns.Set(s);
                break;
	    }
	}

        return ns;
    }

    public void Parse(String _SymbolsFile) {
        SymbolsFile = _SymbolsFile;

	try {
           DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
           DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();

           Document doc = docBuilder.parse (new File(SymbolsFile));

           // normalize text representation
           doc.getDocumentElement().normalize();
           //System.out.println("Root element of the doc is " + doc.getDocumentElement().getNodeName());

           NodeList listOfSymbols = doc.getElementsByTagName("symbol");
           int totalSymbols = listOfSymbols.getLength();
           System.out.println("Total no of symbols : " + totalSymbols);

           for (int i = 0; i < listOfSymbols.getLength(); i++) {
	       Node symbolNode = listOfSymbols.item(i);
               if (symbolNode.getNodeType() == Node.ELEMENT_NODE) {
		   Element symbolElement = (Element) symbolNode;

                   NodeList addrList    = symbolElement.getElementsByTagName("address");
                   Element  addrElement = (Element) addrList.item(0);
                   NodeList addrFnList  = addrElement.getChildNodes();

                   NodeList fileList    = symbolElement.getElementsByTagName("file");
                   Element  fileElement = (Element) fileList.item(0);
                   NodeList fileFnList  = fileElement.getChildNodes();

                   NodeList lineList    = symbolElement.getElementsByTagName("line");
                   Element  lineElement = (Element) lineList.item(0);
                   NodeList lineFnList  = lineElement.getChildNodes();

                   long   address = Long.decode(((Node)addrFnList.item(0)).getNodeValue().trim());
                   String file    = ((Node)fileFnList.item(0)).getNodeValue().trim();
                   int    line    = Integer.parseInt(((Node)lineFnList.item(0)).getNodeValue().trim());

                   Symbol ns = new Symbol();
                   ns.Set(address,file,line);
                   symbols.add(ns);
	       }
	   }
        } catch (SAXException e) {
           Exception x = e.getException ();
           ((x == null) ? e : x).printStackTrace ();
        } catch (Throwable t) {
           t.printStackTrace ();
        }
    }

}
