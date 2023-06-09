package woo.app.transactions;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;
import woo.core.StoreManager;
import woo.core.Transaction;
//FIXME import other classes
import woo.app.exception.UnknownTransactionKeyException;

/**
 * Show specific transaction.
 */
public class DoShowTransaction extends Command<StoreManager> {

	Input<Integer> _transactionID;

  public DoShowTransaction(StoreManager receiver) {
    super(Label.SHOW_TRANSACTION, receiver);
    _transactionID = _form.addIntegerInput(Message.requestTransactionKey());
  }

  @Override
  public final void execute() throws DialogException {

		_form.parse();

	  try {

		Transaction transaction =  _receiver.getTransaction(_transactionID.value());
		_display.addLine(transaction.showTransaction(_receiver.getCurrentDate()));
		_display.display();
	  }catch(woo.core.exception.UnknownTransactionKeyException utke) {
		  throw new UnknownTransactionKeyException(utke.getKey());
	  }
  }
}
