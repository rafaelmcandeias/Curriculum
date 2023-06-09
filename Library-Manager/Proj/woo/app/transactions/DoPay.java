package woo.app.transactions;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.app.exception.UnknownTransactionKeyException;

import woo.core.StoreManager;

/**
 * Pay transaction (sale).
 */
public class DoPay extends Command<StoreManager> {


	Input<Integer> _sale;

  public DoPay(StoreManager storefront) {
    super(Label.PAY, storefront);
    _sale = _form.addIntegerInput(Message.requestTransactionKey());
  }

  @Override
  public final void execute() throws DialogException {

		_form.parse();

	  try {
		  _receiver.pay(_sale.value());
	  }catch(woo.core.exception.UnknownTransactionKeyException utke) {
		  throw new UnknownTransactionKeyException(utke.getKey());
	  }catch(woo.core.exception.NoPaymentStrategy nps) {
		  System.err.println(nps.getMessage());
	  }
  }
}
