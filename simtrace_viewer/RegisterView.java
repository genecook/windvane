package simtrace_viewer;

import javafx.beans.property.SimpleStringProperty;

public class RegisterView {
  private final SimpleStringProperty Name  = new SimpleStringProperty("");
  private final SimpleStringProperty Value = new SimpleStringProperty("");

  public RegisterView() {
      this("","");
  }
      public RegisterView(String Name,String Value) {
            setName(Name);
	    setValue(Value);
	}

	public String getName()               { return Name.get(); };
	public void   setName(String _name)   { Name.set(_name);   };

	public String getValue()              { return Value.get(); };
	public void   setValue(String _value) { Value.set(_value);  };
}