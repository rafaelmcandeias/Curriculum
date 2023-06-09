package woo.app.main;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;
import woo.core.StoreManager;
import woo.core.exception.UnavailableFileException;
import woo.app.exception.FileOpenFailedException;

/**
 * Open existing saved state.
 */
public class DoOpen extends Command<StoreManager> {

  Input<String> _fileName;

  /** @param receiver */
  public DoOpen(StoreManager receiver) {
    super(Label.OPEN, receiver);

    _fileName = _form.addStringInput(Message.openFile());
  }

  /** @see pt.tecnico.po.ui.Command#execute() */
  @Override
  public final void execute() throws DialogException {

    try {
        _form.parse();
        _receiver.load(_fileName.value());
    } catch (UnavailableFileException ufe) {
      throw new FileOpenFailedException(ufe.getFilename());
    }


  }

}
