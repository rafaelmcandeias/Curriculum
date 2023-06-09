package woo.app.products;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.core.StoreManager;

import woo.app.exception.UnknownServiceTypeException;
import woo.app.exception.DuplicateProductKeyException;
import woo.app.exception.UnknownSupplierKeyException;


/**
 * Register box.
 */
public class DoRegisterProductBox extends Command<StoreManager> {

  Input<String> _boxID;
  Input<String> _supplierID;
  Input<Integer> _price;
  Input<Integer> _criticalValue;
  Input<String> _serviceLevel;

  public DoRegisterProductBox(StoreManager receiver) {
    super(Label.REGISTER_BOX, receiver);
    _boxID = _form.addStringInput(Message.requestProductKey());
    _price = _form.addIntegerInput(Message.requestPrice());
    _criticalValue = _form.addIntegerInput(Message.requestStockCriticalValue());
    _supplierID = _form.addStringInput(Message.requestSupplierKey());
    _serviceLevel = _form.addStringInput(Message.requestServiceType());
  }

  @Override
  public final void execute() throws DialogException {

    _form.parse();

    try{
      _receiver.registerBox(_boxID.value(), _supplierID.value(),
      _price.value(), _criticalValue.value(), _serviceLevel.value());
    } catch(woo.core.exception.DuplicateProductKeyException dpke){
      throw new DuplicateProductKeyException(dpke.getKey());
    }catch(woo.core.exception.UnknownServiceTypeException usle){
      throw new UnknownServiceTypeException(usle.getServiceType());
    } catch(woo.core.exception.UnknownSupplierKeyException uske) {
    	throw new UnknownSupplierKeyException(uske.getKey());
    }
  }
}
