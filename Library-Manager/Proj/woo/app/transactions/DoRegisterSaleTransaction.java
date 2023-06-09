package woo.app.transactions;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.core.StoreManager;

import woo.app.exception.UnknownClientKeyException;
import woo.app.exception.UnavailableProductException;
import woo.app.exception.UnknownProductKeyException;

/**
 * Register sale.
 */
public class DoRegisterSaleTransaction extends Command<StoreManager> {

  Input<String> _clientID;
  Input<Integer> _paymentDeadline;
  Input<String> _productID;
  Input<Integer> _quantity;


  public DoRegisterSaleTransaction(StoreManager receiver) {
    super(Label.REGISTER_SALE_TRANSACTION, receiver);

    _clientID = _form.addStringInput(Message.requestClientKey());
    _paymentDeadline = _form.addIntegerInput(Message.requestPaymentDeadline());
    _productID = _form.addStringInput(Message.requestProductKey());
    _quantity = _form.addIntegerInput(Message.requestAmount());
  }

  @Override
  public final void execute() throws DialogException {

    _form.parse();

    try{
      _receiver.registerSale(_clientID.value(), _paymentDeadline.value(), _productID.value(), _quantity.value());
    }catch(woo.core.exception.UnavailableProductException upe){
      throw new UnavailableProductException(upe.getKey(), upe.getRequested(), upe.getAvailable());
    }catch(woo.core.exception.UnknownProductKeyException upke){
      throw new UnknownProductKeyException(upke.getKey());
    }catch(woo.core.exception.UnknownClientKeyException ucke){
      throw new UnknownClientKeyException(ucke.getKey());
    }
  }

}
