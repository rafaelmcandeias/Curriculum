package woo.app.suppliers;

import java.util.Iterator;
import java.util.List;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;
import woo.app.exception.UnknownSupplierKeyException;
import woo.core.StoreManager;
import woo.core.Transaction;
//FIXME import other classes

/**
 * Show all transactions for specific supplier.
 */
public class DoShowSupplierTransactions extends Command<StoreManager> {


	Input<String> _supplierID;

  public DoShowSupplierTransactions(StoreManager receiver) {
    super(Label.SHOW_SUPPLIER_TRANSACTIONS, receiver);
    _supplierID = _form.addStringInput(Message.requestSupplierKey());
  }

  @Override
  public void execute() throws DialogException {

		_form.parse();

	  try {

		  List<Transaction> orders = _receiver.getSupplierTransactions(_supplierID.value());
		  Iterator<Transaction> itr = orders.iterator();

		  while(itr.hasNext()) {
			  Transaction order = itr.next();

			  _display.addLine(order.showTransaction(_receiver.getCurrentDate()));
		  }

		  _display.display();

	  }catch(woo.core.exception.UnknownSupplierKeyException uske) {
	  		throw new UnknownSupplierKeyException(uske.getKey());
	  }
  }
}
