package woo.app.clients;

import java.util.Iterator;
import java.util.List;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.app.exception.UnknownClientKeyException;
import woo.core.Sale;
import woo.core.StoreManager;

/**
 * Show all transactions for a specific client.
 */
public class DoShowClientTransactions extends Command<StoreManager> {

	Input<String> _clientID;

  public DoShowClientTransactions(StoreManager storefront) {
    super(Label.SHOW_CLIENT_TRANSACTIONS, storefront);
    _clientID = _form.addStringInput(Message.requestClientKey());
  }

  @Override
  public void execute() throws DialogException {

		_form.parse();

	  try {

		  List<Sale> _purchases = _receiver.getClientPurchases(_clientID.value());
		  Iterator<Sale> itr = _purchases.iterator();

		  while(itr.hasNext()) {
			  Sale purchase = itr.next();
			  _display.addLine(purchase.showTransaction(_receiver.getCurrentDate()));
		  }

		  _display.display();

	  }catch(woo.core.exception.UnknownClientKeyException ucke){
	      throw new UnknownClientKeyException(ucke.getKey());
	    }
  }

}
