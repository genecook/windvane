package simtrace_viewer;

import scaffold_SAPI.ScaffoldSAPI.*;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.InputStreamReader;
import java.io.IOException;
import java.io.PrintStream;
import java.io.File;
import javafx.stage.FileChooser;
import javafx.stage.Stage;

import javafx.event.ActionEvent;
import javafx.event.Event;
import javafx.scene.control.TextArea;
import javafx.scene.control.TextField;
import javafx.scene.control.Button;
import javafx.scene.control.Tooltip;
import javafx.scene.control.CheckBox;
import javafx.scene.control.TableView;
import javafx.scene.control.TreeTableView;
import javafx.scene.control.ListView;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.beans.property.SimpleStringProperty;

import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseEvent;
import javafx.scene.input.InputEvent;
import javafx.scene.input.KeyCode;
import javafx.scene.input.KeyEvent;
import javafx.scene.input.MouseButton;

import javafx.scene.control.Dialog;
import javafx.scene.control.Alert;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.control.TextInputDialog;
import javafx.scene.control.ChoiceDialog;
import javafx.scene.control.*;

import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.effect.DropShadow;

import java.lang.Character;

import java.io.*;
import java.util.*;

import java.nio.file.*;

import javax.swing.*;

import simtrace_viewer.InstrView;
import simtrace_viewer.RegisterView;
import simtrace_viewer.TranslationView;
import simtrace_viewer.MemoryView;
import simtrace_viewer.RegisterDecode;


public class SimTraceController {
   public TextField MyTrace;

   Scaffold my_scaffold;

   @FXML private ListView<String> listBoxMain;
   @FXML private TableView<InstrView> tableView;

   @FXML private TextField MyCore;
   @FXML private TextField MyBlock;
   @FXML private TextField MyInstrCount;
   @FXML private TextField MyPC;
   @FXML private TextField MyPstate;
   @FXML private TextField MyClock;
   @FXML private TextField MyDisassembly;

   @FXML private TableView<RegisterView> cpuBaseRegisters;
   @FXML private TableView<RegisterView> cpuConfigRegisters;
   @FXML private TableView<RegisterView> cpuProcidRegisters;
   @FXML private TableView<RegisterView> cpuFpuRegisters;
   @FXML private TableView<RegisterView> cpuDebugRegisters;
   @FXML private TableView<RegisterView> cpuExcepRegisters;
   @FXML private TableView<RegisterView> cpuVmsaRegisters;
   @FXML private TableView<RegisterView> cpuResetRegisters;
   @FXML private TableView<RegisterView> cpuThreadRegisters;
   @FXML private TableView<RegisterView> cpuGiccRegisters;
   @FXML private TableView<RegisterView> cpuTimerRegisters;

   @FXML private TableView<TranslationView> translationsTableView;
   @FXML private TableView<MemoryView> memoryTableView;

    
    String trace_file = "cpu.simtrace";

    //public static Long ClockArg = -1;

    public int myCore() {
	int core_num = 0;   // ASSUME core # is 0...

	if (Main.CoreIndexArg >= 0) {
	    // core # specified via command line argument...
            core_num = Main.CoreIndexArg;
	} else if ((MyCore.getText() != null) && !MyCore.getText().trim().equals("")) {
	    // core # specified via gui...
            core_num = Integer.parseInt(MyCore.getText());
	} else {
            // none specified...
	}
	
	//System.out.format("Core: %d\n",core_num);
        return core_num;
    }

    int num_cores = 1;

    public void setCoreCount(int _num_cores) {
        num_cores = _num_cores;
    }
    
    public int coreCount() {
	return num_cores;
    }
    
    public Cpu myCpu() {
       Cpu my_cpu = my_scaffold.getCore(myCore());

       return my_cpu;
    }

    int block_count = 1;

    public void setBlockCount(int _block_count) {
	block_count = _block_count;
    }

    public int blockCount() {
	return block_count;
    }

    public void initialize() {
       if (!Main.SimTraceFileArg.equals("")) { 
	   String trace_file = "";
	  
	   if (Main.SimTraceFileArg.endsWith(".top")) {
	      trace_file = loadMPtrace(Main.SimTraceFileArg);
	   } else {
              trace_file = Main.SimTraceFileArg;
	   }

           loadTrace(trace_file);
       }
    }

    public void doExit(ActionEvent actionEvent) { Quit(); }

    private void Quit() {
        Alert alert = getConfirmationAlert("Exit","","Exit sim-trace viewer?");
        alert.showAndWait();

        if (alert.getResult() == ButtonType.YES) {
            System.out.println("Exiting...\n");
            System.exit(0);
        }
    }
    
    public void doAbout(ActionEvent actionEvent) {
	Alert alert = getInformationAlert("About a64sim sim-trace viewer","",
                                          "Use the sim-trace viewer to view simulation traces produced\nby the a64sim simulator.");
        alert.showAndWait();
    }
    
    private ImageView getLogo() {
        return new ImageView(new Image("file:./images/logo.png"));
    }
    private String getStandardTitle(String _title_postfix) {
        String _title = "a64sim";
        if (!_title_postfix.equals("")) {
                _title = _title + " - " + _title_postfix;
        }
        return _title;
    }

    private Alert getInformationAlert(String _title,String _header,String _infoQuery) {
        Alert alert = new Alert(AlertType.INFORMATION, "Tuleta Software Co. 2017. All rights reserved.", ButtonType.OK);
        alert.setGraphic(getLogo());
        alert.setTitle(getStandardTitle(_title));
        alert.setHeaderText((_header.equals("") ? "a64sim 1.0.4 Alpha\nTuleta Software Co. 2018. All rights reserved." : _header));
        alert.setContentText(_infoQuery);
        return alert;
    }
    private Alert getConfirmationAlert(String _title,String _header,String _infoQuery) {
        Alert alert = new Alert(AlertType.CONFIRMATION, "Tuleta Software Co. 2017. All rights reserved.", ButtonType.YES, ButtonType.CANCEL);
        alert.setGraphic(getLogo());
        alert.setTitle(getStandardTitle(_title));
        alert.setHeaderText((_header.equals("") ? "a64sim 1.0.4\nTuleta Software Co. 2018. All rights reserved." : _header));
        alert.setContentText(_infoQuery);
        return alert;
    }

    //------------------------------------------------------------------------------------------------------------
    // use file chooser popup to locate top-level (trace-history) file, then load the trace...
    //------------------------------------------------------------------------------------------------------------
    
    public void loadTrace(ActionEvent actionEvent) {
          FileChooser fileChooser = new FileChooser();
	 
	  FileChooser.ExtensionFilter filter = new FileChooser.ExtensionFilter("Top level trace file", "*.top");
	  fileChooser.getExtensionFilters().add(filter);
	  
          File selectedFile = fileChooser.showOpenDialog(null);

          if (selectedFile != null) {
             System.out.println("File selected: " + selectedFile.getPath());
          }
          else {
             System.out.println("File selection cancelled.");
             return;
          }

	  String trace_or_top_file = selectedFile.getPath();

	  String trace_file = "";
	  
	  if (trace_or_top_file.endsWith(".top")) {
	      trace_file = loadMPtrace(trace_or_top_file);
	  } else {
              trace_file = trace_or_top_file;
	  }

          loadTrace(trace_file);
    }

    //------------------------------------------------------------------------------------------------------------
    // load 'MP' trace - actually all sim-traces have a top-level (trace history) file. A list of simulation
    //     instruction trace block files are contained in the trace-history. Cause a particular trace block
    //     to be loaded based on the current block #...
    //------------------------------------------------------------------------------------------------------------

    TraceHistory my_trace_history;
    
    String filepath_prefix = "";

    // once a top-level trace has been loaded, the individual trace blocks may be 'traversed'...
    
    public String blockFilePath(int block_id) {
       String load_filepath = "";

       if (filepath_prefix.equals("")) {
	   // top-level trace has yet to be loaded...
       } else if (block_id >= blockCount()) {
	   // invalid block ID...
       } else {
	   String load_filename = my_trace_history.getEpochs(block_id).getBlockFile();
	   load_filepath = filepath_prefix + "/" + load_filename;
       }

       return load_filepath;
    }
    
    public String loadMPtrace(String trace_history_file) {
        System.out.format("Top level trace 'history' file: %s...\n",trace_history_file);
	
        String load_filepath = "";
    
        try {
           my_trace_history = TraceHistory.parseFrom(new FileInputStream(trace_history_file));
	   // we're just going to start at time zero...
	   Path p = FileSystems.getDefault().getPath(trace_history_file);
	   filepath_prefix = p.getParent().toString();
	   String load_filename = my_trace_history.getEpochs(0).getBlockFile();
	   load_filepath = filepath_prefix + "/" + load_filename;
	   setCoreCount(my_trace_history.getNumCores());
	   System.out.format("# of cores in trace: %d\n",coreCount());
	   setBlockCount(my_trace_history.getEpochsCount());
	   System.out.format("# of blocks in trace: %d\n",blockCount());
	   
	   System.out.format("# of instrs in trace: %d\n",my_trace_history.getNumInstrs());
	   System.out.format("# of epochs in trace: %d\n",my_trace_history.getEpochsCount());
	   
        } catch(FileNotFoundException e) {
           System.out.format("File %s not found.\n",trace_history_file);
        } catch(IOException e) {
           System.out.format("Unable to open file %s.",trace_history_file);
        }

        System.out.format("'Time zero' trace file: %s...\n",load_filepath);

	return load_filepath;
    }
    
    //------------------------------------------------------------------------------------------------------------
    // load specified trace block file...
    //------------------------------------------------------------------------------------------------------------

    public void loadTrace(String _load_file) {
       trace_file = _load_file;

       MyTrace.setText(trace_file);

       System.out.format("Loading from sim trace file: %s...\n",trace_file);

       try {
          my_scaffold = Scaffold.parseFrom(new FileInputStream(trace_file));

	  System.out.println("Scaffold parsed...");

          Cpu my_cpu = myCpu();

          ObservableList<String> data = listBoxMain.getItems();

          data.clear();

          for (int i = 0; i < my_cpu.getSliceCount(); i++) {
              CpuSlice my_slice = my_cpu.getSlice(i);
	      Packet pkt = my_slice.getTrace();
  	      data.add(new String(String.format("0x%08x %s",pkt.getPC(),pkt.getDisassembly())));
	  }

          loadTranslations(my_cpu);
	  
          System.out.println("Done.\n");

          if (Main.ClockArg >= 0) {
	      // clock value to advance to specified via command line arg...
	      gotoPacketByClock(Main.ClockArg);
	  } else {
	      // 'reset' current instr index, then go there...
	      current_instr = 0;
              gotoPacket();
	      updateUserInstrCount();
	  }
        } catch(FileNotFoundException e) {
	   System.out.format("File %s not found.\n",trace_file);
        } catch(IOException e) {
	   System.out.format("Unable to open file %s.",trace_file);
        }

       MyCore.setText(String.format("%s",myCore()));
    }

    
    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    final int BLOCKSIZE = 64;
    final int BLOCKOFFSETMASK = BLOCKSIZE - 1;
    
    public void loadMemory(Cpu my_cpu) {
        HashMap<Long, byte[]> mem = new HashMap<Long, byte[]>();

        Long current_pc_block_addr = 0L;
	
	for (int i = 0; i <= CurrentInstruction(); i++) {
            CpuSlice my_slice = my_cpu.getSlice(i);
	    Packet pkt = my_slice.getTrace();
	    if (pkt.getState() < 4)
		continue;

	    // instruction opcode there in packet/decode...

	    int  pc_block_offset = (int) (pkt.getPC() & BLOCKOFFSETMASK); // 64 byte block offset
	    Long pc_block_addr = pkt.getPC() - pc_block_offset; // block address

	    current_pc_block_addr = pc_block_addr;
	    
	    byte bmem[] = mem.get(pc_block_addr);
	    if (bmem == null) {
	       bmem = new byte[BLOCKSIZE];
	       for (int boff = 0; boff < BLOCKSIZE; boff++) {
		   bmem[boff] = 0; // undefined, ASSUME zero
	       }
	    }
            Decode dcd = pkt.getDecode();
	    int _opcode = dcd.getOpcode();
            bmem[pc_block_offset + 3] = (byte) ((_opcode>>24) & 0xff);
            bmem[pc_block_offset + 2] = (byte) ((_opcode>>16) & 0xff);
	    bmem[pc_block_offset + 1] = (byte) ((_opcode>>8)  & 0xff);
	    bmem[pc_block_offset + 0] = (byte) (_opcode & 0xff);
	    mem.put(pc_block_addr,bmem);

	    
	    // mem-ops data there in packet...
            AccessMemory mops = pkt.getMemOps();
    
            for (int j = 0; j < mops.getMOpsMemoryCount(); j++) {
                MemoryAccess ma = mops.getMOpsMemory(j);
	        Long _addr = ma.getAddress();

		int  block_offset = (int) (_addr & BLOCKOFFSETMASK); // 64 byte block offset
		Long block_addr   = _addr - block_offset; // block address

		bmem = mem.get(block_addr);
		
		if (bmem == null) {
		    bmem = new byte[BLOCKSIZE];
		    for (int boff = 0; boff < BLOCKSIZE; boff++) {
			bmem[boff] = 0; // undefined, ASSUME zero
		    }
		}
		
                int _size = ma.getSize();
                byte[] _mbuf = ma.getMembuffer().toByteArray();

		if ((block_offset + _size) >= BLOCKSIZE) {
		  // oops! the last data address goes past this block. need to process two blocks...
		  int bl_index = block_offset;
		  int k = 0;
                  for (k = 0; (k < _size) & (bl_index < BLOCKSIZE); k++) {
		     bmem[bl_index] = _mbuf[k];
		     bl_index += 1;
		  }
  		  mem.put(block_addr,bmem);

		  // process 'spill over' data...
		 
		  block_addr += BLOCKSIZE;
		  bmem = mem.get(block_addr);
		  
		  if (bmem == null) {
		    bmem = new byte[BLOCKSIZE];
		    for (int boff = 0; boff < BLOCKSIZE; boff++) {
			bmem[boff] = 0; // undefined, ASSUME zero
		    }
		  }
		  bl_index = 0;
                  for (k = k; k < _size; k++) {
		     bmem[bl_index] = _mbuf[k];
		     bl_index += 1;
		  }
  		  mem.put(block_addr,bmem);
		  
		} else {
                  for (int k = 0; k < _size; k++) {
		     bmem[block_offset + k] = _mbuf[k];
		  }
  		  mem.put(block_addr,bmem);
		}
		
	    }   
	}

       	ObservableList<MemoryView> data = memoryTableView.getItems();

        data.clear();

	int current_instr = 0;
	
	SortedSet<Long> keys = new TreeSet<Long>(mem.keySet());

	int icnt = 0;
	for (Long key : keys) {
	   
	   byte bmem[] = mem.get(key);

	   String _mb = "";

	   int bcnt = 0;
	   
           for (int k = 0; k < 64; k++) {
	      _mb += String.format("%02x",bmem[k]);
	      bcnt += 1;
	      if (bcnt == 8) {
		  _mb += " ";
		  bcnt = 0;
	      }
	   }

	   _mb += " ";

	   // display printable memory values...
	   
           for (int k = 0; k < 64; k++) {
	       // use printable ascii values...
	       if ( (bmem[k] >= 0x20) && (bmem[k] < 0x7f) ) {
	         char c = (char)(bmem[k] & 0xff);
	       	 _mb += String.format("%c",c);
	       } else {
		   // non-printable, just use '.'...
		 _mb += ".";
	       }
	   }

	   data.add(new MemoryView(String.format("0x%08x",key),_mb));

	   if (key.equals(current_pc_block_addr)) {
	       current_instr = icnt;
	   }
	   
	   icnt++;
	}

	// scroll memory view to current_pc_block_addr

	memoryTableView.getSelectionModel().select(current_instr);
        memoryTableView.getFocusModel().focus(current_instr);
        memoryTableView.scrollTo(current_instr);

	memoryTableView.setTableMenuButtonVisible(true);	
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void ScrollMemoryView(Long addr) {
	int  block_offset = (int) (addr & BLOCKOFFSETMASK); // 64 byte block offset
	Long block_addr = addr - block_offset; // block address
	
	ObservableList<MemoryView> data = memoryTableView.getItems();

	int mindex = 0;
	
	for (MemoryView mb : data) {
	   long next_block_addr = Long.parseLong(mb.getADDR().substring(2),16);
           if (block_addr.equals(next_block_addr)) {
	       break;
	   }
	   mindex += 1;
	}

	// scroll memory view to selected (block) address...

	memoryTableView.getSelectionModel().select(mindex);
        memoryTableView.getFocusModel().focus(mindex);
        memoryTableView.scrollTo(mindex);	
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void loadTranslations(Cpu my_cpu) {
       	ObservableList<TranslationView> data = translationsTableView.getItems();

        data.clear();

	for (int i = 0; i < my_cpu.getTranslationsCount(); i++) {
              Translation my_trans = my_cpu.getTranslations(i);
	      Hashtable<String,String> tparms = new Hashtable<String,String>();
	      tparms.put("LA",String.format("0x%x",my_trans.getLA()));
	      tparms.put("Global",my_trans.hasGlobal() ? String.format("%b",my_trans.getGlobal()) : "-");
	      tparms.put("ASID",my_trans.hasGlobal() && (my_trans.getGlobal()==false) ? String.format("0x%x",my_trans.getASID()) : "-");
              tparms.put("NS",String.format("%b",my_trans.getNS()));

	      boolean is_data  = my_trans.getIsData();
	      
	      tparms.put("Data",is_data ? "DATA" : "INSTR");
	      if (is_data) 
		  tparms.put("Write",my_trans.getIsWrite() ? "WRITE" : "READ");
	      else
		  tparms.put("Write","-");

	      boolean mmu_on = my_trans.getMmuEnabled();
	      
	      tparms.put("MMUEnabled",String.format("%b",mmu_on));

	      //tparms.put("SecondStage",mmu_on ? String.format("%b",my_trans.getSecondstage()) : "-");
	      tparms.put("PermissionCheck",String.format("%b",my_trans.getPermissioncheck()));

	      boolean addr_ext = mmu_on && my_trans.hasAddressExtended() && my_trans.getAddressExtended();
	      
	      tparms.put("AddressExtended",mmu_on && my_trans.hasAddressExtended() ? String.format("%b",my_trans.getAddressExtended()) : "-");
              tparms.put("Aligned",String.format("%b",my_trans.getWasaligned()));
              tparms.put("Size",String.format("%d",my_trans.getSize()));
              tparms.put("Privileged",String.format("%b",my_trans.getPrivileged()));
              tparms.put("ExtendedLA",mmu_on && addr_ext && my_trans.hasExtLA() ? String.format("0x%x",my_trans.getExtLA()) : "-");
              tparms.put("IPA",mmu_on && my_trans.hasIPA() ? String.format("0x%x",my_trans.getIPA()) : "-");
              tparms.put("PA",String.format("0x%x",my_trans.getPA()));
              tparms.put("BigEndian",is_data && mmu_on && my_trans.hasBigEndian() ? String.format("%b",my_trans.getBigEndian()) : "-");
              tparms.put("TopBit",my_trans.hasTopBit() ? String.format("%d",my_trans.getTopBit()) : "-");

	      //tparms.put("S1Enabled",mmu_on && my_trans.hasS1Enabled() ? String.format("%b",my_trans.getS1Enabled()) : "-");
              //tparms.put("S2Enabled",mmu_on && my_trans.hasS2Enabled() ? String.format("%b",my_trans.getS2Enabled()) : "-");

	      tparms.put("TTBBaseAddress",mmu_on && my_trans.hasTtbBaseAddress() ? String.format("0x%x",my_trans.getTtbBaseAddress()) : "-");
	      tparms.put("TBI",my_trans.hasTbi() ? String.format("%b",my_trans.getTbi()) : "-");

	      tparms.put("ReadUnprivileged",my_trans.hasReadUnprivileged() ? String.format("%b",my_trans.getReadUnprivileged()) : "-");
	      tparms.put("WriteUnprivileged",my_trans.hasWriteUnprivileged() ? String.format("%b",my_trans.getWriteUnprivileged()) : "-");
	      tparms.put("ReadPrivileged",my_trans.hasReadPrivileged() ? String.format("%b",my_trans.getReadPrivileged()) : "-");
	      tparms.put("WritePrivileged",my_trans.hasWritePrivileged() ? String.format("%b",my_trans.getWritePrivileged()) : "-");

	      tparms.put("XN",mmu_on ? String.format("%b",my_trans.getXN()) : "false");
	      tparms.put("PXN",mmu_on ? String.format("%b",my_trans.getPXN()) : "false");

	      tparms.put("Contiguous",mmu_on && my_trans.hasContiguous() ? String.format("%b",my_trans.getContiguous()) : "-");
	      tparms.put("nG",my_trans.hasNG() ? String.format("%b",my_trans.getNG()) : "-");
	      tparms.put("AF",my_trans.hasAF() ? String.format("%b",my_trans.getAF()) : "-");

	      switch(my_trans.getMemoryType()) {
                case 0:  tparms.put("MemoryType","Device"); break;
                case 1:  tparms.put("MemoryType","Normal"); break;
	        default: tparms.put("MemoryType","?");      break;
	      }
	      if (my_trans.getMemoryType() == 1) {
		  tparms.put("DeviceType","-");
	      } else {
	        switch(my_trans.getDeviceType()) {
                  case 0:  tparms.put("DeviceType","nGnRnE");  break;
                  case 1:  tparms.put("DeviceType","nGnRE");   break;
                  case 2:  tparms.put("DeviceType","nGRE");    break;
                  case 3:  tparms.put("DeviceType","GRE");     break;
                  case 4:  tparms.put("DeviceType","Unknown"); break;
	          default: tparms.put("DeviceType","?");       break;
	        }
	      }

	      switch(my_trans.getOuterCacheType()) {
                case 0:  tparms.put("OuterCacheType","Write Thru");    break;
                case 1:  tparms.put("OuterCacheType","Write Back");    break;
                case 2:  tparms.put("OuterCacheType","Non Cacheable"); break;		    
	        default: tparms.put("OuterCacheType","?");             break;		  
	      }		  
	      tparms.put("OuterTransient",String.format("%b",my_trans.getOuterTransient()));
	      tparms.put("OuterReadAllocate",String.format("%b",my_trans.getOuterReadAllocate()));
	      tparms.put("OuterWriteAllocate",String.format("%b",my_trans.getOuterWriteAllocate()));

	      switch(my_trans.getInnerCacheType()) {
                case 0:  tparms.put("InnerCacheType","Write Thru");    break;
                case 1:  tparms.put("InnerCacheType","Write Back");    break;
                case 2:  tparms.put("InnerCacheType","Non Cacheable"); break;		    
	        default: tparms.put("InnerCacheType","?");             break;		  
	      }
	      tparms.put("InnerTransient",String.format("%b",my_trans.getInnerTransient()));
	      tparms.put("InnerReadAllocate",String.format("%b",my_trans.getInnerReadAllocate()));
	      tparms.put("InnerWriteAllocate",String.format("%b",my_trans.getInnerWriteAllocate()));

	      tparms.put("OuterShareable",String.format("%b",my_trans.getOutershareable()));
              tparms.put("InnerShareable",String.format("%b",my_trans.getInnershareable()));

	      tparms.put("Domain",String.format("%d",my_trans.getDomain()));
              //tparms.put("Level",my_trans.getLevel() > 0 ? String.format("%d",my_trans.getLevel()) : "-");
              tparms.put("BlockSize",mmu_on && my_trans.hasBlocksize() ? String.format("0x%x",my_trans.getBlocksize()) : "-");
              //tparms.put("Unpredictable",my_trans.hasUnpredictable() ? String.format("%b",my_trans.getUnpredictable()) : "-");
              tparms.put("Levels",mmu_on && my_trans.hasLevels() ? String.format("%d",my_trans.getLevels()) : "-");
              tparms.put("BaseAddress",mmu_on ? String.format("0x%x",my_trans.getBaseAddress()) : "-");
              tparms.put("PageOffsetMask",mmu_on ? String.format("0x%x",my_trans.getPageOffsetMask()) : "-");

              data.add(new TranslationView(tparms));
	}

	translationsTableView.setTableMenuButtonVisible(true);
    }

    //------------------------------------------------------------------------------------------------------------
    // getCpuBaseLevelRegs - get any base reg updates from 'slice'. use to update current cpu register state...
    //------------------------------------------------------------------------------------------------------------
    
    public HashMap<String, String> getCpuBaseLevelRegs(CpuSlice my_slice) {
        BaseLevel my_base = my_slice.getBase();

        HashMap<String, String> bregs = new HashMap<String, String>();

        if (my_base.hasSPEL0()) bregs.put("SP_EL0",String.format("0x%x",my_base.getSPEL0()));
        if (my_base.hasSPEL1()) bregs.put("SP_EL1",String.format("0x%x",my_base.getSPEL1()));
        if (my_base.hasSPEL2()) bregs.put("SP_EL2",String.format("0x%x",my_base.getSPEL2()));
        if (my_base.hasSPEL3()) bregs.put("SP_EL3",String.format("0x%x",my_base.getSPEL3()));

        for (int i = 0; i < my_base.getGPCount(); i++) {
	    GPRegister gpreg = my_base.getGP(i);
	    bregs.put(String.format("X%d",gpreg.getKey()), String.format("0x%x",gpreg.getVal()));
	}

	// ASSUME floating pt unit is there...
	
        FPU my_fpu = my_slice.getFpu();
	
        for (int i = 0; i < my_fpu.getVCount(); i++) {
	    SimdReg vreg = my_fpu.getV(i);
	    String rval_hi_decoded = vreg.hasRvalHiDecoded() ? "(" + vreg.getRvalHiDecoded() + ") " : "";
	    String rval_lo_decoded = vreg.hasRvalLoDecoded() ? "(" + vreg.getRvalLoDecoded() + ") " : "";
	    bregs.put(String.format("V[%d]",vreg.getKey()),
		      String.format("127..64: 0x%x %s/ 63..0: 0x%x %s",vreg.getRvalHi(),rval_hi_decoded,vreg.getRvalLo(),rval_lo_decoded));
	}
	
        return bregs;
     }

    //------------------------------------------------------------------------------------------------------------
    // update 'displayed' cpu register state...
    //------------------------------------------------------------------------------------------------------------
    
    public void updateCpuBaseLevelRegs(HashMap<String, String> regs) {
	// update base (application level) regs...

       	ObservableList<RegisterView> cpu_regs = cpuBaseRegisters.getItems();
        cpu_regs.clear();

        boolean have_regs = false;

	// for user convenience, add registers to display, in order, gp regs then fp regs...

	int add_cnt = 0;
	
	for (int i = 0; i < 32; i++) {
	    String gpreg = String.format("X%d",i);
	    if (regs.containsKey(gpreg)) {
		cpu_regs.add( new RegisterView(gpreg,regs.get(gpreg) ) );
                add_cnt += 1;
                have_regs = true;
	    }
	}
	for (int i = 0; i < 32; i++) {
	    String simdreg = String.format("V[%d]",i);
	    if (regs.containsKey(simdreg)) {
		cpu_regs.add( new RegisterView(simdreg,regs.get(simdreg) ) );
                add_cnt += 1;
                have_regs = true;
	    }
	}

	if (add_cnt != regs.size()) {

	}

	// previously, added regs in no particular order...
/*
        Set set = regs.entrySet();
        Iterator iterator = set.iterator();
	
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           cpu_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }
*/
	
        if (!have_regs) cpu_regs.add(new RegisterView("","")); //<---make sure something is in table
    }


    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public HashMap<String, String> getCpuConfigRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        BaseLevel my_base = my_slice.getBase();
        if (my_base.hasSCREL3()) regs.put("SCR_EL3", String.format("0x%x (%s)",my_base.getSCREL3(),RegisterDecode.SCR_EL3(my_base.getSCREL3())));

        Configuration my_cfg = my_slice.getCfg();

        if (my_cfg.hasIDAA64DFR0EL1())
	    regs.put("ID_AA64DFR0_EL1", String.format("0x%x (%s)",my_cfg.getIDAA64DFR0EL1(), RegisterDecode.ID_AA64DFR0_EL1(my_cfg.getIDAA64DFR0EL1()) ) );
        if (my_cfg.hasIDAA64MMFR0EL1())
	    regs.put("ID_AA64MMFR0_EL1",String.format("0x%x (%s)",my_cfg.getIDAA64MMFR0EL1(), RegisterDecode.ID_AA64MMFR0_EL1(my_cfg.getIDAA64MMFR0EL1()) ) );
        if (my_cfg.hasIDAA64PFR0EL1())
	    regs.put("ID_AA64PFR0_EL1", String.format("0x%x (%s)",my_cfg.getIDAA64PFR0EL1(), RegisterDecode.ID_AA64PFR0_EL1(my_cfg.getIDAA64PFR0EL1())  ) );
        if (my_cfg.hasIDAA64ISAR0EL1())
	    regs.put("ID_AA64ISAR0_EL1",String.format("0x%x (%s)",my_cfg.getIDAA64ISAR0EL1(), RegisterDecode.ID_AA64ISAR0_EL1(my_cfg.getIDAA64ISAR0EL1())  ));

        if (my_cfg.hasMIDREL1())  regs.put("MIDR_EL1", String.format("0x%x (%s)",my_cfg.getMIDREL1(), RegisterDecode.MIDR_EL1(my_cfg.getMIDREL1())  ));
        if (my_cfg.hasVPIDREL2()) regs.put("VPIDR_EL2",String.format("0x%x (%s)",my_cfg.getVPIDREL2(), RegisterDecode.VPIDR_EL2(my_cfg.getVPIDREL2())  ));
        if (my_cfg.hasCTREL0())   regs.put("CTR_EL0",  String.format("0x%x (%s)",my_cfg.getCTREL0(), RegisterDecode.CTR_EL0(my_cfg.getCTREL0())  ));
        if (my_cfg.hasDCZIDEL0()) regs.put("DCZID_EL0",String.format("0x%x (%s)",my_cfg.getDCZIDEL0(), RegisterDecode.DCZID_EL0(my_cfg.getDCZIDEL0())  ));

        if (my_cfg.hasRVBAREL1()) regs.put("RVBAR_EL1",String.format("0x%x",my_cfg.getRVBAREL1()));
        if (my_cfg.hasRVBAREL2()) regs.put("RVBAR_EL2",String.format("0x%x",my_cfg.getRVBAREL2()));
        if (my_cfg.hasRVBAREL3()) regs.put("RVBAR_EL3",String.format("0x%x",my_cfg.getRVBAREL3()));

        if (my_cfg.hasAFSR0EL1()) regs.put("AFSR0_EL1",String.format("0x%x",my_cfg.getAFSR0EL1()));
        if (my_cfg.hasAFSR0EL2()) regs.put("AFSR0_EL2",String.format("0x%x",my_cfg.getAFSR0EL2()));
        if (my_cfg.hasAFSR0EL3()) regs.put("AFSR0_EL3",String.format("0x%x",my_cfg.getAFSR0EL3()));
        if (my_cfg.hasAFSR1EL1()) regs.put("AFSR1_EL1",String.format("0x%x",my_cfg.getAFSR1EL1()));
        if (my_cfg.hasAFSR1EL2()) regs.put("AFSR1_EL2",String.format("0x%x",my_cfg.getAFSR1EL2()));
        if (my_cfg.hasAFSR1EL3()) regs.put("AFSR1_EL3",String.format("0x%x",my_cfg.getAFSR1EL3()));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuConfigRegs(HashMap<String, String> src_regs) {
        // update Configuration regs...
       	ObservableList<RegisterView> cfg_regs = cpuConfigRegisters.getItems();
        cfg_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           cfg_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) cfg_regs.add(new RegisterView("","")); //<---make sure something is in table
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public HashMap<String, String> getCpuProcidRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        ProcID my_procids = my_slice.getIds();

        if (my_procids.hasMPIDREL1())  regs.put("MPIDR_EL1",  String.format("0x%x (%s)", my_procids.getMPIDREL1(), RegisterDecode.MPIDR_EL1(my_procids.getMPIDREL1())     ));
        if (my_procids.hasVMPIDREL2()) regs.put("VMPIDR_EL2", String.format("0x%x (%s)", my_procids.getVMPIDREL2(), RegisterDecode.VMPIDR_EL2(my_procids.getVMPIDREL2())  ));
        if (my_procids.hasREVIDREL1()) regs.put("REVIDR_EL1", String.format("0x%x",      my_procids.getREVIDREL1(), RegisterDecode.REVIDR_EL1(my_procids.getREVIDREL1())  ));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuProcidRegs(HashMap<String, String> src_regs) {
        // update ProcID regs...
       	ObservableList<RegisterView> procid_regs = cpuProcidRegisters.getItems();
        procid_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           procid_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) procid_regs.add(new RegisterView("","")); //<---make sure something is in table
    }

    //------------------------------------------------------------------------------------------------------------
    // getCpuFpuRegs - get any float reg updates from 'slice'. use to update current cpu register state...
    //------------------------------------------------------------------------------------------------------------
    
    public HashMap<String, String> getCpuFpuRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        FPU my_fpu = my_slice.getFpu();

        if (my_fpu.hasCPACREL1()) regs.put("CPACR_EL1", String.format("0x%x (%s)",my_fpu.getCPACREL1(), RegisterDecode.CPACR_EL1(my_fpu.getCPACREL1()) ));
        if (my_fpu.hasCPTREL2())  regs.put("CPTR_EL2",  String.format("0x%x (%s)",my_fpu.getCPTREL2(),  RegisterDecode.CPTR_EL2(my_fpu.getCPTREL2()) ));
        if (my_fpu.hasCPTREL3())  regs.put("CPTR_EL3",  String.format("0x%x (%s)",my_fpu.getCPTREL3(),  RegisterDecode.CPTR_EL3(my_fpu.getCPTREL3()) ));
        if (my_fpu.hasFPCR())     regs.put("FPCR",      String.format("0x%x (%s)",my_fpu.getFPCR(),     RegisterDecode.FPCR(my_fpu.getFPCR()) ));
        if (my_fpu.hasFPSR())     regs.put("FPSR",      String.format("0x%x (%s)",my_fpu.getFPSR(),     RegisterDecode.FPSR(my_fpu.getFPSR(),true) ));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    // update 'displayed' cpu register state...
    //------------------------------------------------------------------------------------------------------------
    
    public void updateCpuFpuRegs(HashMap<String, String> src_regs) {
        // update FPU regs...
       	ObservableList<RegisterView> fpu_regs = cpuFpuRegisters.getItems();
        fpu_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           fpu_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) fpu_regs.add(new RegisterView("","")); //<---make sure something is in table
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public HashMap<String, String> getCpuDebugRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        Debug my_dbg = my_slice.getDbg();

        if (my_dbg.hasMDSCREL1())      regs.put("MDSCR_EL1",      String.format("0x%x",my_dbg.getMDSCREL1()));
        if (my_dbg.hasMDCCSREL0())     regs.put("MDCCSR_EL0",     String.format("0x%x",my_dbg.getMDCCSREL0()));
        if (my_dbg.hasDBGDTREL0())     regs.put("DBGDTR_EL0",     String.format("0x%x",my_dbg.getDBGDTREL0()));
        if (my_dbg.hasDBGDTRRXEL0())   regs.put("DBGDTRRX_EL0",   String.format("0x%x",my_dbg.getDBGDTRRXEL0()));
        if (my_dbg.hasDBGDTRTXEL0())   regs.put("DBGDTRTX_EL0",   String.format("0x%x",my_dbg.getDBGDTRTXEL0()));
        if (my_dbg.hasDLREL0())        regs.put("DLR_EL0",        String.format("0x%x",my_dbg.getDLREL0()));
        if (my_dbg.hasDSPSREL0())      regs.put("DSPSR_EL0",      String.format("0x%x",my_dbg.getDSPSREL0()));
        if (my_dbg.hasCONTEXTIDREL1()) regs.put("CONTEXTIDR_EL1", String.format("0x%x",my_dbg.getCONTEXTIDREL1()));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuDebugRegs(HashMap<String, String> src_regs) {
        // update Debug regs...
       	ObservableList<RegisterView> dbg_regs = cpuDebugRegisters.getItems();
        dbg_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           dbg_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) dbg_regs.add(new RegisterView("","")); //<---make sure something is in table
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public HashMap<String, String> getCpuExcepRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        ExceptionState my_exc = my_slice.getExcep();

        if (my_exc.hasSPSREL1()) regs.put("SPSR_EL1", String.format("0x%x (%s)", my_exc.getSPSREL1(), RegisterDecode.SPSR_EL1( my_exc.getSPSREL1() )  ));
        if (my_exc.hasSPSREL2()) regs.put("SPSR_EL2", String.format("0x%x (%s)", my_exc.getSPSREL2(), RegisterDecode.SPSR_EL2( my_exc.getSPSREL2() )  ));
        if (my_exc.hasSPSREL3()) regs.put("SPSR_EL3", String.format("0x%x (%s)", my_exc.getSPSREL3(), RegisterDecode.SPSR_EL3( my_exc.getSPSREL3() )  ));
        if (my_exc.hasELREL1())  regs.put("ELR_EL1",  String.format("0x%x",      my_exc.getELREL1()));
        if (my_exc.hasELREL2())  regs.put("ELR_EL2",  String.format("0x%x",      my_exc.getELREL2()));
        if (my_exc.hasELREL3())  regs.put("ELR_EL3",  String.format("0x%x",      my_exc.getELREL3()));
        if (my_exc.hasESREL1())  regs.put("ESR_EL1",  String.format("0x%x (%s)", my_exc.getESREL1(),  RegisterDecode.ESR_EL1(  my_exc.getESREL1()  )  ));
        if (my_exc.hasESREL2())  regs.put("ESR_EL2",  String.format("0x%x (%s)", my_exc.getESREL2(),  RegisterDecode.ESR_EL2(  my_exc.getESREL2()  )  ));
        if (my_exc.hasESREL3())  regs.put("ESR_EL3",  String.format("0x%x (%s)", my_exc.getESREL3(),  RegisterDecode.ESR_EL3(  my_exc.getESREL3()  )  ));
        if (my_exc.hasFAREL1())  regs.put("FAR_EL1",  String.format("0x%x",      my_exc.getFAREL1()));
        if (my_exc.hasFAREL2())  regs.put("FAR_EL2",  String.format("0x%x",      my_exc.getFAREL2()));
        if (my_exc.hasFAREL3())  regs.put("FAR_EL3",  String.format("0x%x",      my_exc.getFAREL3()));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuExcepRegs(HashMap<String, String> src_regs) {
        // update ExceptionState regs...
       	ObservableList<RegisterView> exc_regs = cpuExcepRegisters.getItems();
        exc_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           exc_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) exc_regs.add(new RegisterView("","")); //<---make sure something is in table
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public HashMap<String, String> getCpuVmsaRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        VMSA my_vmsa = my_slice.getMmu();

        if (my_vmsa.hasVBAREL1())  regs.put("VBAR_EL1",  String.format("0x%x",my_vmsa.getVBAREL1()));
        if (my_vmsa.hasVBAREL2())  regs.put("VBAR_EL2",  String.format("0x%x",my_vmsa.getVBAREL2()));
        if (my_vmsa.hasVBAREL3())  regs.put("VBAR_EL3",  String.format("0x%x",my_vmsa.getVBAREL3()));
        if (my_vmsa.hasTCREL1())   regs.put("TCR_EL1",   String.format("0x%x (%s)",my_vmsa.getTCREL1(),    RegisterDecode.TCR_EL1(my_vmsa.getTCREL1())  ));
        if (my_vmsa.hasTCREL2())   regs.put("TCR_EL2",   String.format("0x%x (%s)",my_vmsa.getTCREL2(),    RegisterDecode.TCR_EL2(my_vmsa.getTCREL2())  ));
        if (my_vmsa.hasTCREL3())   regs.put("TCR_EL3",   String.format("0x%x (%s)",my_vmsa.getTCREL3(),    RegisterDecode.TCR_EL3(my_vmsa.getTCREL3())  ));
        if (my_vmsa.hasMAIREL1())  regs.put("MAIR_EL1",  String.format("0x%x (%s)",my_vmsa.getMAIREL1(),   RegisterDecode.MAIR_EL1(my_vmsa.getMAIREL1())  ));
        if (my_vmsa.hasMAIREL2())  regs.put("MAIR_EL2",  String.format("0x%x (%s)",my_vmsa.getMAIREL2(),   RegisterDecode.MAIR_EL2(my_vmsa.getMAIREL2())  ));
        if (my_vmsa.hasMAIREL3())  regs.put("MAIR_EL1",  String.format("0x%x (%s)",my_vmsa.getMAIREL3(),   RegisterDecode.MAIR_EL3(my_vmsa.getMAIREL3())  ));
        if (my_vmsa.hasSCTLREL1()) regs.put("SCTLR_EL1", String.format("0x%x (%s)",my_vmsa.getSCTLREL1(),  RegisterDecode.SCTLR_EL1(my_vmsa.getSCTLREL1())  ));
        if (my_vmsa.hasSCTLREL2()) regs.put("SCTLR_EL2", String.format("0x%x (%s)",my_vmsa.getSCTLREL2(),  RegisterDecode.SCTLR_EL2(my_vmsa.getSCTLREL2())  ));
        if (my_vmsa.hasSCTLREL3()) regs.put("SCTLR_EL3", String.format("0x%x (%s)",my_vmsa.getSCTLREL3(),  RegisterDecode.SCTLR_EL3(my_vmsa.getSCTLREL3())  ));
        if (my_vmsa.hasTTBR0EL1()) regs.put("TTBR0_EL1", String.format("0x%x (%s)",my_vmsa.getTTBR0EL1(),  RegisterDecode.TTBR0_EL1(my_vmsa.getTTBR0EL1())  ));
        if (my_vmsa.hasTTBR1EL1()) regs.put("TTBR1_EL1", String.format("0x%x (%s)",my_vmsa.getTTBR1EL1(),  RegisterDecode.TTBR1_EL1(my_vmsa.getTTBR1EL1())  ));
        if (my_vmsa.hasTTBR0EL2()) regs.put("TTBR0_EL2", String.format("0x%x (%s)",my_vmsa.getTTBR0EL2(),  RegisterDecode.TTBR0_EL2(my_vmsa.getTTBR0EL2())  ));
        if (my_vmsa.hasTTBR0EL3()) regs.put("TTBR0_EL3", String.format("0x%x (%s)",my_vmsa.getTTBR0EL3(),  RegisterDecode.TTBR0_EL3(my_vmsa.getTTBR0EL3())  ));
        if (my_vmsa.hasHCREL2())   regs.put("HCR_EL2",   String.format("0x%x (%s)",my_vmsa.getHCREL2(),    RegisterDecode.HCR_EL2(my_vmsa.getHCREL2())  ));
        if (my_vmsa.hasPAREL1())   regs.put("PAR_EL1",   String.format("0x%x (%s)",my_vmsa.getPAREL1()));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuVmsaRegs(HashMap<String, String> src_regs) {
        // update VMSA regs...
       	ObservableList<RegisterView> vmsa_regs = cpuVmsaRegisters.getItems();
        vmsa_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           vmsa_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) vmsa_regs.add(new RegisterView("","")); //<---make sure something is in table
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public HashMap<String, String> getCpuResetRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        ResetMgmt my_reset = my_slice.getReset();        

        if (my_reset.hasRMREL1()) regs.put("RMR_EL1", String.format("0x%x",my_reset.getRMREL1()));
        if (my_reset.hasRMREL2()) regs.put("RMR_EL2", String.format("0x%x",my_reset.getRMREL2()));
        if (my_reset.hasRMREL3()) regs.put("RMR_EL3", String.format("0x%x",my_reset.getRMREL3()));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuResetRegs(HashMap<String, String> src_regs) {
        // update ResetMgmt regs...
       	ObservableList<RegisterView> rst_regs = cpuResetRegisters.getItems();
        rst_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           rst_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) rst_regs.add(new RegisterView("","")); //<---make sure something is in table
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public HashMap<String, String> getCpuThreadRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        ThreadRegs my_thr = my_slice.getThread();

        if (my_thr.hasTPIDREL1()) regs.put("TPIDR_EL1", String.format("0x%x",my_thr.getTPIDREL1()));
        if (my_thr.hasTPIDREL2()) regs.put("TPIDR_EL2", String.format("0x%x",my_thr.getTPIDREL2()));
        if (my_thr.hasTPIDREL3()) regs.put("TPIDR_EL3", String.format("0x%x",my_thr.getTPIDREL3()));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuThreadRegs(HashMap<String, String> src_regs) {
        // update Thread regs...
       	ObservableList<RegisterView> thr_regs = cpuThreadRegisters.getItems();
        thr_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           thr_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) thr_regs.add(new RegisterView("","")); //<---make sure something is in table
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public HashMap<String, String> getCpuGiccRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        GICSystemRegs my_gicc = my_slice.getGicSregs();

        if (my_gicc.hasICCPMREL1()) regs.put("ICC_PMR_EL1", String.format("0x%x",my_gicc.getICCPMREL1()));
        if (my_gicc.hasICCIAR0EL1()) regs.put("ICC_IAR0_EL1", String.format("0x%x",my_gicc.getICCIAR0EL1()));
        if (my_gicc.hasICCEORI0EL1()) regs.put("ICC_EORI0_EL1", String.format("0x%x",my_gicc.getICCEORI0EL1()));
        if (my_gicc.hasICCHPPIR0EL1()) regs.put("ICC_HPPIR0_EL1", String.format("0x%x",my_gicc.getICCHPPIR0EL1()));
        if (my_gicc.hasICCBPR0EL1()) regs.put("ICC_BPR0_EL1", String.format("0x%x",my_gicc.getICCBPR0EL1()));
        if (my_gicc.hasICCAP0R0EL1()) regs.put("ICC_AP0R0_EL1", String.format("0x%x",my_gicc.getICCAP0R0EL1()));
        if (my_gicc.hasICCAP0R1EL1()) regs.put("ICC_AP0R1_EL1", String.format("0x%x",my_gicc.getICCAP0R1EL1()));
        if (my_gicc.hasICCAP0R2EL1()) regs.put("ICC_AP0R2_EL1", String.format("0x%x",my_gicc.getICCAP0R2EL1()));
        if (my_gicc.hasICCAP0R3EL1()) regs.put("ICC_AP0R3_EL1", String.format("0x%x",my_gicc.getICCAP0R3EL1()));
        if (my_gicc.hasICCAP1R1EL1()) regs.put("ICC_AP1R1_EL1", String.format("0x%x",my_gicc.getICCAP1R1EL1()));
        if (my_gicc.hasICCAP1R2EL1()) regs.put("ICC_AP1R2_EL1", String.format("0x%x",my_gicc.getICCAP1R2EL1()));
        if (my_gicc.hasICCAP1R3EL1()) regs.put("ICC_AP1R3_EL1", String.format("0x%x",my_gicc.getICCAP1R3EL1()));
        if (my_gicc.hasICCDIREL1()) regs.put("ICC_DIR_EL1", String.format("0x%x",my_gicc.getICCDIREL1()));
        if (my_gicc.hasICCRPREL1()) regs.put("ICC_RPR_EL1", String.format("0x%x",my_gicc.getICCRPREL1()));
        if (my_gicc.hasICCSGI1REL1()) regs.put("ICC_SGI1R_EL1", String.format("0x%x",my_gicc.getICCSGI1REL1()));
        if (my_gicc.hasICCASGI1REL1()) regs.put("ICC_ASGI1R_EL1", String.format("0x%x",my_gicc.getICCASGI1REL1()));
        if (my_gicc.hasICCSGI0REL1()) regs.put("ICC_SGI0R_EL1", String.format("0x%x",my_gicc.getICCSGI0REL1()));
        if (my_gicc.hasICCIAR1EL1()) regs.put("ICC_IAR1_EL1", String.format("0x%x",my_gicc.getICCIAR1EL1()));
        if (my_gicc.hasICCEOIR1EL1()) regs.put("ICC_EOIR1_EL1", String.format("0x%x",my_gicc.getICCEOIR1EL1()));
        if (my_gicc.hasICCHPPIR1EL1()) regs.put("ICC_HPPIR1_EL1", String.format("0x%x",my_gicc.getICCHPPIR1EL1()));
        if (my_gicc.hasICCBPR1EL1()) regs.put("ICC_BPR1_EL1", String.format("0x%x",my_gicc.getICCBPR1EL1()));
        if (my_gicc.hasICCCTLREL1()) regs.put("ICC_CTLR_EL1", String.format("0x%x",my_gicc.getICCCTLREL1()));
        if (my_gicc.hasICCSREEL1()) regs.put("ICC_SRE_EL1", String.format("0x%x",my_gicc.getICCSREEL1()));
        if (my_gicc.hasICCIGRPEN0EL1()) regs.put("ICC_IGRPEN0_EL1", String.format("0x%x",my_gicc.getICCIGRPEN0EL1()));
        if (my_gicc.hasICCIGRPEN1EL1()) regs.put("ICC_IGRPEN1_EL1", String.format("0x%x",my_gicc.getICCIGRPEN1EL1()));
        if (my_gicc.hasICCSREEL2()) regs.put("ICC_SRE_EL2", String.format("0x%x",my_gicc.getICCSREEL2()));
        if (my_gicc.hasICCCTLREL3()) regs.put("ICC_CTLR_EL3", String.format("0x%x",my_gicc.getICCCTLREL3()));
        if (my_gicc.hasICCSREEL3()) regs.put("ICC_SRE_EL3", String.format("0x%x",my_gicc.getICCSREEL3()));
        if (my_gicc.hasICCIGRPEN1EL3()) regs.put("ICC_IGRPEN1_EL3", String.format("0x%x",my_gicc.getICCIGRPEN1EL3()));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuGiccRegs(HashMap<String, String> src_regs) {
        // update Thread regs...
       	ObservableList<RegisterView> gicc_regs = cpuGiccRegisters.getItems();
        gicc_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           gicc_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) gicc_regs.add(new RegisterView("","")); //<---make sure something is in table
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public HashMap<String, String> getCpuTimerRegs(CpuSlice my_slice) {
        HashMap<String, String> regs = new HashMap<String, String>();

        GenericTimer my_timer = my_slice.getTimer();

        if (my_timer.hasCNTFRQEL0()) regs.put("CNTFRQ_EL0", String.format("0x%x",my_timer.getCNTFRQEL0()));
        if (my_timer.hasCNTHCTLEL2()) regs.put("CNTHCTL_EL2", String.format("0x%x",my_timer.getCNTHCTLEL2()));
        if (my_timer.hasCNTHPCTLEL2()) regs.put("CNTHP_CTL_EL2", String.format("0x%x",my_timer.getCNTHPCTLEL2()));
        if (my_timer.hasCNTHPCVALEL2()) regs.put("CNTHP_CVAL_EL2", String.format("0x%x",my_timer.getCNTHPCVALEL2()));
        if (my_timer.hasCNTHPTVALEL2()) regs.put("CNTHP_TVAL_EL2", String.format("0x%x",my_timer.getCNTHPTVALEL2()));
        if (my_timer.hasCNTKCTLEL1()) regs.put("CNTKCTL_EL1", String.format("0x%x",my_timer.getCNTKCTLEL1()));
        if (my_timer.hasCNTPCTLEL0()) regs.put("CNTP_CTL_EL0", String.format("0x%x",my_timer.getCNTPCTLEL0()));
        if (my_timer.hasCNTPCVALEL0()) regs.put("CNTP_CVAL_EL0", String.format("0x%x",my_timer.getCNTPCVALEL0()));
        if (my_timer.hasCNTPTVALEL0()) regs.put("CNTP_TVAL_EL0", String.format("0x%x",my_timer.getCNTPTVALEL0()));
        if (my_timer.hasCNTPCTEL0()) regs.put("CNTPCT_EL0", String.format("0x%x",my_timer.getCNTPCTEL0()));
        if (my_timer.hasCNTPSCTLEL1()) regs.put("CNTPS_CTL_EL1", String.format("0x%x",my_timer.getCNTPSCTLEL1()));
        if (my_timer.hasCNTPSCVALEL1()) regs.put("CNTPS_CVAL_EL1", String.format("0x%x",my_timer.getCNTPSCVALEL1()));
        if (my_timer.hasCNTPSTVALEL1()) regs.put("CNTPS_TVAL_EL1", String.format("0x%x",my_timer.getCNTPSTVALEL1()));
        if (my_timer.hasCNTVCTLEL0()) regs.put("CNTV_CTL_EL0", String.format("0x%x",my_timer.getCNTVCTLEL0()));
        if (my_timer.hasCNTVCVALEL0()) regs.put("CNTV_CVAL_EL0", String.format("0x%x",my_timer.getCNTVCVALEL0()));
        if (my_timer.hasCNTVTVALEL0()) regs.put("CNTV_TVAL_EL0", String.format("0x%x",my_timer.getCNTVTVALEL0()));
        if (my_timer.hasCNTVCTEL0()) regs.put("CNTVCT_EL0", String.format("0x%x",my_timer.getCNTVCTEL0()));
        if (my_timer.hasCNTVOFFEL2()) regs.put("CNTVOFF_EL2", String.format("0x%x",my_timer.getCNTVOFFEL2()));

        return regs;
    }

    //------------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuTimerRegs(HashMap<String, String> src_regs) {
        // update Timer regs...
       	ObservableList<RegisterView> timer_regs = cpuTimerRegisters.getItems();
        timer_regs.clear();

        Set set = src_regs.entrySet();
        Iterator iterator = set.iterator();
        boolean have_regs = false;
        while(iterator.hasNext()) {
           Map.Entry mentry = (Map.Entry)iterator.next();
           timer_regs.add(new RegisterView((String) mentry.getKey(),(String) mentry.getValue() ) );
           have_regs = true;
        }

        if (!have_regs) timer_regs.add(new RegisterView("","")); //<---make sure something is in table
    }
    

    //------------------------------------------------------------------------------------------------------------
    // foreach cpu register group:
    //   get cpu state from cpu initial state
    //   from 0 to current_instr:
    //     get slice reg state and apply to cpu state
    //   display cpu state
    //------------------------------------------------------------------------------------------------------------

    public void updateCpuRegState(boolean last_instr) {
        Cpu my_cpu = myCpu();

        HashMap<String, String> basregs   = getCpuBaseLevelRegs(my_cpu.getInitialState());
        HashMap<String, String> cfgregs   = getCpuConfigRegs(my_cpu.getInitialState());
        HashMap<String, String> pidregs   = getCpuProcidRegs(my_cpu.getInitialState());
        HashMap<String, String> fpuregs   = getCpuFpuRegs(my_cpu.getInitialState());
        HashMap<String, String> dbgregs   = getCpuDebugRegs(my_cpu.getInitialState());
        HashMap<String, String> excregs   = getCpuExcepRegs(my_cpu.getInitialState());
        HashMap<String, String> mmuregs   = getCpuVmsaRegs(my_cpu.getInitialState());
        HashMap<String, String> rstregs   = getCpuResetRegs(my_cpu.getInitialState());
        HashMap<String, String> thrregs   = getCpuThreadRegs(my_cpu.getInitialState());
        HashMap<String, String> giccregs  = getCpuGiccRegs(my_cpu.getInitialState());
        HashMap<String, String> timerregs = getCpuTimerRegs(my_cpu.getInitialState());

        int icnt = current_instr;
        if (last_instr) icnt += 1;

        for (int i = 0; i < icnt; i++) {
	    basregs.putAll(getCpuBaseLevelRegs(my_cpu.getSlice(i)));
            cfgregs.putAll(getCpuConfigRegs(my_cpu.getSlice(i)));
            pidregs.putAll(getCpuProcidRegs(my_cpu.getSlice(i)));
            fpuregs.putAll(getCpuFpuRegs(my_cpu.getSlice(i)));
            dbgregs.putAll(getCpuDebugRegs(my_cpu.getSlice(i)));
            excregs.putAll(getCpuExcepRegs(my_cpu.getSlice(i)));
            mmuregs.putAll(getCpuVmsaRegs(my_cpu.getSlice(i)));
            rstregs.putAll(getCpuResetRegs(my_cpu.getSlice(i)));
            thrregs.putAll(getCpuThreadRegs(my_cpu.getSlice(i)));
            giccregs.putAll(getCpuGiccRegs(my_cpu.getSlice(i)));
            timerregs.putAll(getCpuTimerRegs(my_cpu.getSlice(i)));
	}

        updateCpuBaseLevelRegs(basregs);
        updateCpuConfigRegs(cfgregs);
        updateCpuProcidRegs(pidregs);
        updateCpuFpuRegs(fpuregs);
        updateCpuDebugRegs(dbgregs);
        updateCpuExcepRegs(excregs);
        updateCpuVmsaRegs(mmuregs);
        updateCpuResetRegs(rstregs);
        updateCpuThreadRegs(thrregs);
        updateCpuGiccRegs(giccregs);
        updateCpuTimerRegs(timerregs);
    }

    private int current_instr = 0;
    private long current_pc = 0;
    private long current_pstate = 0;
    private String pstate_info;	
    private boolean do_scrollto = true;
    
    public int CurrentInstruction() { return current_instr; }

    public void SetScrollToPolicy(boolean _do_scroll) { do_scrollto = _do_scroll; }
    public boolean DoScrollTo() { return do_scrollto; }
    
    public void gotoPacketByClock(long _clock) {
          Cpu my_cpu = myCpu();

          for (int i = 0; i < my_cpu.getSliceCount(); i++) {
              CpuSlice my_slice = my_cpu.getSlice(i);
	      Packet pkt = my_slice.getTrace();
              if (pkt.getClock() == _clock) {
                  current_instr = i;
                  gotoPacket();
		  break;
	      }
	  }
    }

    public boolean advanceToPacketByPC(long _pc, int _current_instr) {
          boolean foundit = false;

          Cpu my_cpu = myCpu();

          for (int i = _current_instr; i < my_cpu.getSliceCount(); i++) {
              CpuSlice my_slice = my_cpu.getSlice(i);
	      Packet pkt = my_slice.getTrace();
              if (pkt.getPC() == _pc) {
                  current_instr = i;
                  foundit = true;
                  gotoPacket();
		  break;
	      }
	  }

          return foundit;
    }

    public void gotoPacketByPC(long _pc) {
        if (advanceToPacketByPC(_pc,current_instr + 1)) {
            // cool. form current instruction was able to advance to next instruction instance with matching pc...
	} else {
            advanceToPacketByPC(_pc,0);
	}
    }

    public void gotoPacket() {
        Cpu my_cpu        = myCpu();
        CpuSlice my_slice = my_cpu.getSlice(current_instr);
	Packet pkt        = my_slice.getTrace();

        gotoPacket(my_cpu,my_slice,pkt);
    }

    public String decodePstate(long pstate) {
	return RegisterDecode.Pstate(pstate);
	
	//long NZCV = (pstate>>28) & 0x0f;
        //long D    = (pstate>>11) & 1;
        //long IL   = (pstate>>17) & 1;
        //long SS   = (pstate>>10) & 1;
        //long A    = (pstate>>8) & 1;
        //long I    = (pstate>>7) & 1;
        //long F    = (pstate>>6) & 1;
        //long EL   = (pstate>>2) & 3;
        //long SP   = (pstate & 1)==1 ? EL : 0;
    
        //return String.format("NZCV=0x%x D=%d IL=%d SS=%d A=%d I=%d F=%d EL%d/SP%d\n",NZCV,D,IL,SS,A,I,F,EL,SP);
        //return String.format("NZCV=0x%x EL%d/SP%d D=%d IL=%d SS=%d A=%d I=%d F=%d \n",NZCV,EL,SP,D,IL,SS,A,I,F);
    }
    
    public void gotoPacket(Cpu my_cpu,CpuSlice my_slice,Packet pkt) {
	String _start_clock = String.format("%d",pkt.getClock());

  	String _pc     = String.format("0x%x",pkt.getPC());
	String _pstate = String.format("0x%x",pkt.getPstate());

	current_pc = pkt.getPC();
	current_pstate = Integer.toUnsignedLong(pkt.getPstate()); //<---do not want pstate value to be sign-extended...

        MyPC.setText( _pc );
        MyPstate.setText( decodePstate(current_pstate) );
	MyPstate.setTooltip(new Tooltip(decodePstate(current_pstate)));

        MyClock.setText( _start_clock );
        MyDisassembly.setText( pkt.getDisassembly() );

	String _goal  = String.format("%d",pkt.getGoal());
	String _group = pkt.getInstrGroup();

        String _state;

	if (pkt.hasExcep()) {
	    _state = pkt.getExcep().getExceptionType();
	} else if (pkt.hasWaiting()) {
	    _state = "WAIT STATE";
	} else {
          switch(pkt.getState()) {
            case 0:   _state = "FREERUN INIT"; break;
            case 1:   _state = "FREERUN RESERVE MEMORY"; break;
            case 2:   _state = "FREERUN SELECT"; break;
            case 3:   _state = "FREERUN ENCODE"; break;
            case 4:   _state = "FREERUN WRITE"; break;
            case 5:   _state = "FREERUN END"; break;
            case 6:   _state = "FETCH"; break;
            case 7:   _state = "DECODE"; break;
            case 8:   _state = "FETCH OPERANDS"; break;
            case 9:   _state = "EXECUTE"; break;
            case 10:  _state = "MEMORY ACCESS"; break;
            case 11:  _state = "WRITEBACK"; break;
            case 12:  _state = "RETIRE"; break;
	    default: _state = "INTERNAL ERROR"; break;
	  }
	}
	
        updateCpuRegState(false);

       	ObservableList<InstrView> data = tableView.getItems();

        data.clear();

	data.add(new InstrView("Goal", _goal,  "",  "",  "",  "",  "",  ""));
	data.add(new InstrView("Instruction group", _group,  "",  "",  "",  "",  "",  ""));

	int last_state = pkt.getState();
	if (pkt.hasExcep() && pkt.getExcep().hasState())
	    last_state = pkt.getExcep().getState();
	
	switch(last_state) {
	  case 6:   // FETCH
	            data.add(new InstrView("State",_state,"","","","","",""));
	            break;
	  case 7:   // DECODE
	            data.add(new InstrView("State","",_state,"","","","",""));
	            break;
	  case 8:   // FETCH OPERANDS
	            data.add(new InstrView("State","","",_state,"","","",""));
	            break;
	  case 9:   // EXECUTE
	            data.add(new InstrView("State","","","",_state,"","",""));
	            break;
	  case 10:  // MEMORY ACCESS
	            data.add(new InstrView("State","","","","",_state,"",""));
	            break;
	  case 11:  // WRITEBACK
	            data.add(new InstrView("State","","","","","", _state,""));
	            break;
	  case 12:  // RETIRE
	            data.add(new InstrView("State","","","","","","", _state));
	            break;
	  default:  // just stick the state on FETCH...
	            data.add(new InstrView("State",_state,"","","","","",""));
	            break;
	}	    

        // FETCH...

        if (pkt.getState() >= 0) {
	    // fetch data there in packet...
            Fetch ftch = pkt.getFetch();
	    String _isize = String.format("%d",ftch.getInstrSizeInBytes());
	    String _asize = String.format("%d",ftch.getAccessSizeInBytes());
	    String _be    = String.format("%b",ftch.getBigEndian());

	    data.add(new InstrView("Instruction Size",_isize, "",  "",  "",  "",  "",  ""));
	    data.add(new InstrView("Access Size",     _asize, "",  "",  "",  "",  "",  ""));
	    data.add(new InstrView("Big Endian",      _be,    "",  "",  "",  "",  "",  ""));
	}

        // DECODE...

        if (pkt.getState() >= 1) {
	    // decode data there in packet...
            Decode dcd = pkt.getDecode();
	    String _opcode         = String.format("0x%4x",dcd.getOpcode());
	    String _primary_opcode = String.format("0x%x",dcd.getPrimaryOpcode());
	    String _instr_enum     = dcd.getA64InstrEnum();
 
	    data.add(new InstrView("Opcode",             "", _opcode,          "",  "",  "",  "",  ""));
	    data.add(new InstrView("Primary opcode",     "", _primary_opcode,  "",  "",  "",  "",  ""));
	    data.add(new InstrView("Instruction enum",   "", _instr_enum,      "",  "",  "",  "",  ""));

            for (int i = 0; i < dcd.getFieldOpsCount(); i++) {
                InstrField fop = dcd.getFieldOps(i);
                String _fname = fop.getKey();
                String _fval  = String.format("%d",fop.getVal());
	        data.add(new InstrView("Field " + _fname,"", _fval,"",  "",  "",  "",  ""));
            }
	}

        // FETCH-OPERANDS...

        if (pkt.getState() >= 2) {
	    // fetch-operands data there in packet...
            FetchOperands fops = pkt.getReadOps();
            for (int i = 0; i < fops.getSrcRegsGPCount(); i++) {
		RegisterUpdate reg = fops.getSrcRegsGP(i);
                String _rname = reg.getKey();
                String _rval = String.format("0x%x",reg.getVal());

	        data.add(new InstrView(_rname, "", "", _rval,  "",  "",  "",  ""));
	    }
            for (int i = 0; i < fops.getSrcRegsSysCount(); i++) {
		RegisterUpdate reg = fops.getSrcRegsSys(i);
                String _rname = reg.getKey();
                String _rval = String.format("0x%x",reg.getVal());

	        data.add(new InstrView(_rname, "", "", _rval,  "",  "",  "",  ""));
	    }
            for (int i = 0; i < fops.getSrcRegsASIMDCount(); i++) {
		SimdReg reg = fops.getSrcRegsASIMD(i);
                String _rname = String.format("V[%d]",reg.getKey());
                String _rval = String.format("0x%x / 0x%x",reg.getRvalHi(),reg.getRvalLo());

	        data.add(new InstrView(_rname, "", "", _rval,  "",  "",  "",  ""));
	    }	    
	}

        // EXECUTE...

        if (pkt.getState() >= 3) {
	    // execute data there in packet...
	}

        // ACCESS-MEMORY...

        if (pkt.getState() >= 4) {
	    // mem-ops data there in packet...
            AccessMemory mops = pkt.getMemOps();

            for (int i = 0; i < mops.getMOpsMemoryCount(); i++) {
                MemoryAccess ma     = mops.getMOpsMemory(i);
                String _addr        = String.format("0x%x",ma.getAddress());
                String _size        = String.format("%d",  ma.getSize());
                String _type        = ma.getType();
                String _excl        = String.format("%b",  ma.getExclusive());
                String _direction   = ma.getDirection();
                String _endianness  = ma.getEndianness();
                String _word_size   = String.format("%d",  ma.getWordSize());
                String _sign_extend = String.format("%b",  ma.getSignExtend());
                String _paired      = String.format("%b",  ma.getPaired());
                String _privileged  = String.format("%b",  ma.getPrivileged());

	        data.add(new InstrView("Access address",  "", "", "",  "", _addr,         "",  ""));
	        data.add(new InstrView("Access size",     "", "", "",  "", _size,         "",  ""));
	        data.add(new InstrView("Access type",     "", "", "",  "", _type,         "",  ""));
	        data.add(new InstrView("Exclusive?",      "", "", "",  "", _excl,         "",  ""));
	        data.add(new InstrView("Direction",       "", "", "",  "", _direction,    "",  ""));
	        data.add(new InstrView("Data endianness", "", "", "",  "", _endianness,   "",  ""));
	        data.add(new InstrView("Word size",       "", "", "",  "", _word_size,    "",  ""));
	        data.add(new InstrView("Sign extend?",    "", "", "",  "", _sign_extend,  "",  ""));
	        data.add(new InstrView("Paired?",         "", "", "",  "", _paired,       "",  ""));
	        data.add(new InstrView("Privileged?",     "", "", "",  "", _privileged,   "",  ""));

		String _excl_passed = "N/A";
		if (ma.getExclusive() && _direction.equals("WRITE")) {
                  _excl_passed = String.format("%b",ma.getExclusivePassed());
		}
	        data.add(new InstrView("Exclusive write successful?", "", "", "", "", _excl_passed, "", ""));
		
                byte[] _mbuf = ma.getMembuffer().toByteArray();
                String _mb = "";
                for (int j = 0; j < _mbuf.length; j++) {
		    _mb += String.format("%02x ",_mbuf[j]);
		}
	        data.add(new InstrView("Data memory",     "", "", "",  "", _mb,   "",  ""));
	    }

	    // scroll translation table to (what should be) the translation for this instruction...
	    
	    for (int i = 0; i < mops.getTranslationsCount(); i++) {
		int translationsIndex = mops.getTranslations(i);
		// if 1st entry, scroll to translation table entry...
		if (i == 0) {
		    translationsTableView.getSelectionModel().select(translationsIndex);
                    translationsTableView.getFocusModel().focus(translationsIndex);
                    translationsTableView.scrollTo(translationsIndex);
		}
		// would be nice to hilight all translation table entries associated with this instr...
	    }
	}

	// WRITEBACK...

        if (pkt.getState() >= 5) {
	    // writeback data there in packet...

            WriteBack wops = pkt.getWriteOps();
            String _next_pc = String.format("0x%04x",wops.getNextPC());
	    
	    String _next_pstate = decodePstate(Integer.toUnsignedLong(wops.getNextPstate()));

	    String _next_fpsr = RegisterDecode.FPSR(wops.getNextFPSR(),false);
		    
	    data.add(new InstrView("Next PC", "", "", "",  "",  "", _next_pc,  ""));
	    data.add(new InstrView("Next Pstate", "", "", "",  "",  "", _next_pstate,  ""));
	    data.add(new InstrView("Next FPSR", "", "", "",  "",  "", _next_fpsr,  ""));

            for (int i = 0; i < wops.getDestRegsGPCount(); i++) {
		RegisterUpdate reg = wops.getDestRegsGP(i);
                String _rname = reg.getKey();
                String _rval = String.format("0x%x",reg.getVal());

	        data.add(new InstrView(_rname, "", "", "",  "",  "", _rval,  ""));
	    }
            for (int i = 0; i < wops.getDestRegsSysCount(); i++) {
		RegisterUpdate reg = wops.getDestRegsSys(i);
                String _rname = reg.getKey();
                String _rval = String.format("0x%x",reg.getVal());

	        data.add(new InstrView(_rname, "", "", "",  "",  "", _rval,  ""));
	    }
            for (int i = 0; i < wops.getDestRegsASIMDCount(); i++) {
		SimdReg reg = wops.getDestRegsASIMD(i);
                String _rname = String.format("V[%d]",reg.getKey());
                String _rval = String.format("0x%x/0x%x",reg.getRvalHi(),reg.getRvalLo());
	        data.add(new InstrView(_rname, "", "", "",  "",  "", _rval,  ""));
	    }
	}

        // RETIRE...

        if (pkt.getState() >= 6) {
	    // retire data there in packet...
	}

        listBoxMain.getSelectionModel().select(current_instr);
        listBoxMain.getFocusModel().focus(current_instr);
	if (DoScrollTo()) {
          listBoxMain.scrollTo(current_instr);
	}
	loadMemory(my_cpu);
    }

   public void handleMouseClick(MouseEvent arg0) {
       current_instr = listBoxMain.getSelectionModel().getSelectedIndex();
       updateUserInstrCount();
       SetScrollToPolicy(false);
       gotoPacket();
       SetScrollToPolicy(true);
       //System.out.println("mouse!.\n");
   }

   public void handleTVMouseClick(MouseEvent arg0) {
       InstrView md = tableView.getSelectionModel().getSelectedItem();

       try {
          if (md.getHeading() == "Access address") {
	    //System.out.printf("Heading: '%s' access-memory: '%s'\n",md.getHeading(),md.getAccessMemory());
	    long addr = Long.parseLong(md.getAccessMemory().substring(2),16);
	    //System.out.printf("Address: 0x%x\n",addr);

	    // get the packet for the currently selected instruction...
	    Cpu my_cpu = myCpu();
            CpuSlice my_slice = my_cpu.getSlice(current_instr);
	    Packet pkt = my_slice.getTrace();

	    // get the memory accesses for this instruction from the packet...
	    AccessMemory mops = pkt.getMemOps();

	    // for each recorded transaction (id into master translations table), see if the address in question
	    // falls within the range of the translation, and if so, scroll the translations table to that translation...
	 
	    for (int i = 0; i < mops.getTranslationsCount(); i++) {
	       int translationsIndex = mops.getTranslations(i);
               Translation my_trans = my_cpu.getTranslations(translationsIndex);
	       if (my_trans.getIsData() && (addr >= my_trans.getLA()) && (addr <= (my_trans.getLA() + my_trans.getBlocksize())) ) {
		   // translation for data block and the selected address falls within the translation - ASSUME this one is it!
	  	   translationsTableView.getSelectionModel().select(translationsIndex);
                   translationsTableView.getFocusModel().focus(translationsIndex);
                   translationsTableView.scrollTo(translationsIndex);
		   break;
	       }
	    }
	    Long laddr = addr;
	    ScrollMemoryView(laddr);
          }
       } catch(NullPointerException e) {
	  // oops. nothing selected...
       }
    }

    public void updateTraceFile(ActionEvent actionEvent) {
       trace_file = MyTrace.getText();
       //System.out.println("Simulation trace file: " + trace_file + "\n");     
    }

    int current_core = -1;
    
    public void gotoCore(int goto_core) {
	//System.out.printf("Selected core: %d\n", goto_core);
	
	if (goto_core >= coreCount()) {
	    // core # requested exceeds # of cores...
	    if (current_core < 0)
		current_core = 0;
	    MyCore.setText( String.format("%d",current_core) );
	} else if (goto_core == current_core) {
	    // same core selected...
	} else {
	    // okay, switch to desired core...
            current_core = goto_core;
	    MyCore.setText( String.format("%d",current_core) );
	    System.out.printf("Switching view to core: %d...\n", goto_core);     
	}	
	gotoCurrentBlock();
    }
    
    public void updateCoreNum(ActionEvent actionEvent) {
	int goto_core = Integer.parseInt(MyCore.getText());

	gotoCore(goto_core);
    }

    int current_block = 0;

    public void gotoBlock(int goto_block) {
	System.out.printf("Selected block: %d\n", goto_block);

	// does indexed block (file) exist?...
	
	String next_blockfile = blockFilePath(goto_block);

	if (next_blockfile.equals("")) {
	    // no blockfile for this ID???
	    MyBlock.setText( String.format("%d",current_block) );
	} else {
	    // okay, switch to desired block...
            current_block = goto_block;
	    System.out.printf("Switching view to block %d...\n", goto_block);     
	    loadTrace(next_blockfile);
	}
    }
    public void gotoCurrentBlock() {
	gotoBlock(current_block);
    }
    
    public void updateBlockNum(ActionEvent actionEvent) {
	int goto_block = Integer.parseInt(MyBlock.getText());

	gotoBlock(goto_block);
    }
    

    public void updateInstrPC(ActionEvent actionEvent) {
	long goto_pc = Long.decode(MyPC.getText());

	gotoPacketByPC(goto_pc);
    }
    
    public void updateInstrClock(ActionEvent actionEvent) {
	long goto_clock = Long.decode(MyClock.getText());
	gotoPacketByClock(goto_clock);
    }

    public void updateInstrCount(ActionEvent actionEvent) {
       int goto_instr = Integer.parseInt(MyInstrCount.getText());

       Cpu my_cpu = myCpu();

       if (goto_instr < 1) {
	   current_instr = 0;
       } else if (goto_instr <= my_cpu.getSliceCount()) {
         current_instr = goto_instr - 1;
         //System.out.println("Current instruction index: " + goto_instr + "\n");
       } else {
         System.out.println("Requested instruction index: " + goto_instr + " is out of bounds. Instead pegging to last instruction of trace\n");
         current_instr = my_cpu.getSliceCount() - 1;
       }

       updateUserInstrCount();
       gotoPacket();
    }

    public void updateUserInstrCount() {
         MyInstrCount.setText( String.format("%d",current_instr + 1) );
    }

    public void doPreviousInstr(ActionEvent actionEvent) {
       if (current_instr >= 1) {
         current_instr -= 1;
         updateUserInstrCount();
       }
       //System.out.format("Previous instruction index: %d\n",current_instr);
       gotoPacket();
    }

    public void doNextInstr(ActionEvent actionEvent) {
        Cpu my_cpu = myCpu();
	if (current_instr < my_cpu.getSliceCount() - 1) {
          current_instr += 1;
          updateUserInstrCount();
          //System.out.format("Next instruction index: %d\n",current_instr);
          gotoPacket();
	} else {
          System.out.println("Already on last instruction of trace. Updating cpu state to reflect updates from last instruction\n");
          updateCpuRegState(true);
	}
    }
}
