package woo.app.products;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;
import woo.core.StoreManager;
import woo.app.exception.UnknownProductKeyException;

/**
 * Change product price.
 */
public class DoChangePrice extends Command<StoreManager> {

  private Input<String> _productID;
  private Input<Integer> _newPrice;

  public DoChangePrice(StoreManager receiver) {
    super(Label.CHANGE_PRICE, receiver);
    _productID = _form.addStringInput(Message.requestProductKey());
    _newPrice = _form.addIntegerInput(Message.requestPrice());
  }

  @Override
  public final void execute() throws DialogException {

    _form.parse();

    try{
      _receiver.setProductPrice(_productID.value(), _newPrice.value());
    }catch(woo.core.exception.UnknownProductKeyException upke){
      throw new UnknownProductKeyException(upke.getKey());
    }

  }
}
