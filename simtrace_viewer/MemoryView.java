package simtrace_viewer;

import javafx.beans.property.SimpleStringProperty;

public class MemoryView {
  private final SimpleStringProperty ADDR = new SimpleStringProperty("");
  private final SimpleStringProperty DATA = new SimpleStringProperty("");

  public MemoryView() {
      this("","");
  }
    public MemoryView(String _ADDR,String _DATA) {
            setADDR(_ADDR);
	    setDATA(_DATA);
	}

	public String getADDR() { return ADDR.get(); };
	public void   setADDR(String _ADDR) { ADDR.set(_ADDR);   };
	public String getDATA() { return DATA.get(); };
	public void   setDATA(String _DATA) { DATA.set(_DATA);  };

}
