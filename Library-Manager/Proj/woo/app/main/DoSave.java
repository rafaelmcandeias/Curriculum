package woo.app.main;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.Input;

import woo.core.StoreManager;
import woo.core.exception.MissingFileAssociationException;

import java.io.*;


/**
 * Save current state to file under current name (if unnamed, query for name).
 */
public class DoSave extends Command<StoreManager> {

  Input<String> _fileName;

  /** @param receiver */
  public DoSave(StoreManager receiver) {
    super(Label.SAVE, receiver);
    _fileName = _form.addStringInput(Message.newSaveAs());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() {

    try{
      _receiver.save();
    } catch(MissingFileAssociationException mfae) {
        _form.parse();
        try{
          _receiver.saveAs(_fileName.value());
        }catch(MissingFileAssociationException e){
          _display.addLine(e.getMessage());
          _display.display();
        }catch(IOException ioe){
          ioe.printStackTrace();
        }

    }catch(IOException ioe){
      ioe.printStackTrace();
    }
  }
}
