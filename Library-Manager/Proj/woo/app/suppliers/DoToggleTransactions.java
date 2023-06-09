package woo.app.suppliers;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.app.exception.UnknownSupplierKeyException;

import woo.core.StoreManager;

/**
 * Enable/disable supplier transactions.
 */
public class DoToggleTransactions extends Command<StoreManager> {

	Input<String> _supplierID;

  public DoToggleTransactions(StoreManager receiver) {
    super(Label.TOGGLE_TRANSACTIONS, receiver);
    _supplierID = _form.addStringInput(Message.requestSupplierKey());
  }

  @Override
  public void execute() throws DialogException {

		_form.parse();

	  try {

		  if(_receiver.toggleTransactions(_supplierID.value())) {
			  _display.addLine(Message.transactionsOn(_supplierID.value()));
		  }else {
			  _display.addLine(Message.transactionsOff(_supplierID.value()));
		  }

		  _display.display();

	  }catch(woo.core.exception.UnknownSupplierKeyException uske) {
		  throw new UnknownSupplierKeyException(uske.getKey());
	  }
  }

}
