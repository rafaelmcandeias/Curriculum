package woo.app.main;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.core.StoreManager;

import woo.app.exception.InvalidDateException;


/**
 * Advance current date.
 */
public class DoAdvanceDate extends Command<StoreManager> {

  private Input<Integer> _days;

  public DoAdvanceDate(StoreManager receiver) {
    super(Label.ADVANCE_DATE, receiver);
    _days = _form.addIntegerInput(Message.requestDaysToAdvance());
  }

  @Override
  public final void execute() throws DialogException {
    _form.parse();

    try{
      _receiver.advanceDate(_days.value());
    }catch(woo.core.exception.InvalidDateException ide){
      throw new InvalidDateException(ide.getDate());
    }
  }
}
