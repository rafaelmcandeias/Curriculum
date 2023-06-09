package woo.app.products;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.core.StoreManager;

import woo.app.exception.UnknownServiceLevelException;
import woo.app.exception.UnknownServiceTypeException;
import woo.app.exception.DuplicateProductKeyException;
import woo.app.exception.UnknownSupplierKeyException;


/**
 * Register container.
 */
public class DoRegisterProductContainer extends Command<StoreManager> {

  Input<String> _containerID;
  Input<String> _supplierID;
  Input<Integer> _price;
  Input<Integer> _criticalValue;
  Input<String> _serviceType;
  Input<String> _serviceLevel;

  public DoRegisterProductContainer(StoreManager receiver) {
    super(Label.REGISTER_CONTAINER, receiver);
    _containerID = _form.addStringInput(Message.requestProductKey());
    _price = _form.addIntegerInput(Message.requestPrice());
    _criticalValue = _form.addIntegerInput(Message.requestStockCriticalValue());
    _supplierID = _form.addStringInput(Message.requestSupplierKey());
    _serviceType = _form.addStringInput(Message.requestServiceType());
    _serviceLevel = _form.addStringInput(Message.requestServiceLevel());
  }

  @Override
  public final void execute() throws DialogException {

    _form.parse();

    try{
      _receiver.registerContainer(_containerID.value(), _supplierID.value(),
      _price.value(), _criticalValue.value(), _serviceType.value() ,_serviceLevel.value());
    }catch(woo.core.exception.DuplicateProductKeyException dpke){
      throw new DuplicateProductKeyException(dpke.getKey());
    } catch(woo.core.exception.UnknownServiceTypeException uste){
       throw new UnknownServiceTypeException(uste.getServiceType());
     }catch(woo.core.exception.UnknownServiceLevelException usle){
       throw new UnknownServiceLevelException(usle.getServiceLevel());
     } catch(woo.core.exception.UnknownSupplierKeyException uske) {
     	throw new UnknownSupplierKeyException(uske.getKey());
     }
  }
}
