package woo.app.suppliers;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;

import woo.core.StoreManager;
import woo.core.Supplier;

import java.util.*;

/**
 * Show all suppliers.
 */
public class DoShowSuppliers extends Command<StoreManager> {

  public DoShowSuppliers(StoreManager receiver) {
    super(Label.SHOW_ALL_SUPPLIERS, receiver);
  }

  @Override
  public void execute() throws DialogException {
    List<Supplier> suppliers = _receiver.getSuppliers();
    Iterator<Supplier> itr = suppliers.iterator();

    while(itr.hasNext()){
      Supplier supplier = itr.next();
      if(supplier.isActive()){
        _display.addLine(supplier.showSupplierData(Message.yes()));
      }else{
        _display.addLine(supplier.showSupplierData(Message.no()));
      }
    }

    _display.display();

  }
}
