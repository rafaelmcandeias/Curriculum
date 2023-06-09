package woo.app.products;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;
import pt.tecnico.po.ui.Input;

import woo.core.StoreManager;

import woo.app.exception.DuplicateProductKeyException;
import woo.app.exception.UnknownSupplierKeyException;


/**
 * Register book.
 */
public class DoRegisterProductBook extends Command<StoreManager> {

  Input<String> _bookID;
  Input<String> _supplierID;
  Input<Integer> _price;
  Input<Integer> _criticalValue;
  Input<String> _title;
  Input<String> _author;
  Input<String> _isbn;

  public DoRegisterProductBook(StoreManager receiver) {
    super(Label.REGISTER_BOOK, receiver);
    _bookID = _form.addStringInput(Message.requestProductKey());
    _title = _form.addStringInput(Message.requestBookTitle());
    _author = _form.addStringInput(Message.requestBookAuthor());
    _isbn = _form.addStringInput(Message.requestISBN());
    _price = _form.addIntegerInput(Message.requestPrice());
    _criticalValue = _form.addIntegerInput(Message.requestStockCriticalValue());
    _supplierID = _form.addStringInput(Message.requestSupplierKey());
  }

  @Override
  public final void execute() throws DialogException {

    _form.parse();

    try{
      _receiver.registerBook(_bookID.value(), _supplierID.value(), _price.value(), _criticalValue.value(), _title.value(), _author.value(), _isbn.value());
    } catch(woo.core.exception.DuplicateProductKeyException dpke){
      throw new DuplicateProductKeyException(dpke.getKey());
    } catch(woo.core.exception.UnknownSupplierKeyException uske) {
    	throw new UnknownSupplierKeyException(uske.getKey());
    }
  }
}
