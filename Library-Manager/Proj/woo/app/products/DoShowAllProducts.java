package woo.app.products;

import java.util.Iterator;
import java.util.List;

import pt.tecnico.po.ui.Command;
import pt.tecnico.po.ui.DialogException;

import woo.core.StoreManager;
import woo.core.Product;

/**
 * Show all products.
 */
public class DoShowAllProducts extends Command<StoreManager> {

  public DoShowAllProducts(StoreManager receiver) {
    super(Label.SHOW_ALL_PRODUCTS, receiver);
  }

  @Override
  public final void execute() throws DialogException {

      List<Product> products = _receiver.getProducts();
      Iterator<Product> itr = products.iterator();

      while(itr.hasNext()){
    	  Product product = itr.next();
    	  _display.addLine(product.showProductData());
      }

      _display.display();
  }

}
