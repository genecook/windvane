package simtrace_viewer;

import java.io.*;
import java.util.*;
import javax.swing.*;
import java.lang.Integer;
import java.io.File;
import org.w3c.dom.Document;
import org.w3c.dom.*;

import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.DocumentBuilder;
import org.xml.sax.SAXException;
import org.xml.sax.SAXParseException; 

import simtrace_viewer.DisasmEntry;

public class Disasm {
    String DisasmFile;      // src disassembly
    String DisasmLinksFile; // src XML file containing links into src disassembly
    List<DisasmEntry> symbols = new ArrayList<DisasmEntry>();

    public void Disasm() {
    }

    public void Dump() {
        System.out.println("Src disasm file (text):      '" + DisasmFile + "'"); 
        System.out.println("Src disasm links file (XML): '" + DisasmLinksFile + "'");
      
        for (DisasmEntry s : symbols) {
	    s.Dump();
	}
    }

    public DisasmEntry Match(long address) {
        DisasmEntry ns = new DisasmEntry();

        for (DisasmEntry s : symbols) {
	    if (s.Match(address)) { 
		ns.Set(s);
                break;
	    } else if (s.Below(address)) {
                ns.Set(s);
            } else if (s.Passed(address)) {
                break;
	    }
	}

        return ns;
    }

    public void Parse(String _DisasmFile, String _DisasmLinksFile) {
        DisasmFile      = _DisasmFile;
        DisasmLinksFile = _DisasmLinksFile;

	try {
           DocumentBuilderFactory docBuilderFactory = DocumentBuilderFactory.newInstance();
           DocumentBuilder docBuilder = docBuilderFactory.newDocumentBuilder();

           Document doc = docBuilder.parse (new File(DisasmLinksFile));

           // normalize text representation
           doc.getDocumentElement().normalize();
           System.out.println("Root element of the doc is " + doc.getDocumentElement().getNodeName());

           NodeList listOfEntries = doc.getElementsByTagName("entry_point");
           int totalEntries = listOfEntries.getLength();
           System.out.println("Total no of entries : " + totalEntries);

           for (int i = 0; i < listOfEntries.getLength(); i++) {
	       Node entryNode = listOfEntries.item(i);
               if (entryNode.getNodeType() == Node.ELEMENT_NODE) {
		   Element entryElement = (Element) entryNode;

                   NodeList addrList    = entryElement.getElementsByTagName("address");
                   Element  addrElement = (Element) addrList.item(0);
                   NodeList addrFnList  = addrElement.getChildNodes();

                   NodeList fnameList    = entryElement.getElementsByTagName("function");
                   Element  fnameElement = (Element) fnameList.item(0);
                   NodeList fnameFnList  = fnameElement.getChildNodes();

                   NodeList lineList    = entryElement.getElementsByTagName("line");
                   Element  lineElement = (Element) lineList.item(0);
                   NodeList lineFnList  = lineElement.getChildNodes();

                   long   address       = Long.decode(((Node)addrFnList.item(0)).getNodeValue().trim());
                   String function_name = ((Node)fnameFnList.item(0)).getNodeValue().trim();
                   int    line          = Integer.parseInt(((Node)lineFnList.item(0)).getNodeValue().trim());

                   DisasmEntry ds = new DisasmEntry();
                   ds.Set(address,function_name,line);
                   symbols.add(ds);
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
