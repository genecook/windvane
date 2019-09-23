package simtrace_viewer;

import javafx.beans.property.SimpleStringProperty;

public class InstrView {
  private final SimpleStringProperty Heading        = new SimpleStringProperty("");
  private final SimpleStringProperty fetch          = new SimpleStringProperty("");
  private final SimpleStringProperty decode         = new SimpleStringProperty("");
  private final SimpleStringProperty fetch_operands = new SimpleStringProperty("");
  private final SimpleStringProperty execute        = new SimpleStringProperty("");
  private final SimpleStringProperty access_memory  = new SimpleStringProperty("");
  private final SimpleStringProperty writeback      = new SimpleStringProperty("");
  private final SimpleStringProperty retire         = new SimpleStringProperty("");

  public InstrView() {
      this("","","","","","","","");
  }
      public InstrView(String Heading,String fetch,String decode,String fetch_operands,String execute,String access_memory,String writeback,String retire) {
            setHeading(Heading);
	    setFetch(fetch);
	    setDecode(decode);
	    setFetchOperands(fetch_operands);
	    setExecute(execute);
            setAccessMemory(access_memory);
            setWriteback(writeback);
            setRetire(retire);
	}

	public String getHeading() { return Heading.get(); };
	public void   setHeading(String _heading) { 
           Heading.set(_heading); 
        };

	public String getFetch() { return fetch.get(); };
	public void setFetch(String _fetch) { fetch.set(_fetch); };

	public String getDecode() { return decode.get(); };
	public void setDecode(String _decode) { decode.set(_decode); };

	public String getFetchOperands() { return fetch_operands.get(); };
	public void setFetchOperands(String _fetch_operands) { fetch_operands.set(_fetch_operands); };

	public String getExecute() { return execute.get(); };
	public void setExecute(String _execute) { execute.set(_execute); };

	public String getAccessMemory() { return access_memory.get(); };
	public void setAccessMemory(String _memory) { access_memory.set(_memory); };

	public String getWriteback() { return writeback.get(); };
	public void setWriteback(String _writeback) { writeback.set(_writeback); };

	public String getRetire() { return retire.get(); };
	public void setRetire(String _retire) { retire.set(_retire); };
}
