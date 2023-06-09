package woo.app.main;

import pt.tecnico.po.ui.Command;

import woo.core.StoreManager;

/**
 * Show global balance.
 */
public class DoShowGlobalBalance extends Command<StoreManager> {


  public DoShowGlobalBalance(StoreManager receiver) {
    super(Label.SHOW_BALANCE, receiver);
  }

  @Override
  public final void execute() {
    _display.addLine(Message.currentBalance(_receiver.getAvailableBalance(), _receiver.getAccountingBalance()));
    _display.display();
  }
}
