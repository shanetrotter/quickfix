/****************************************************************************
** Copyright (c) quickfixengine.org  All rights reserved.
**
** This file is part of the QuickFIX FIX Engine
**
** This file may be distributed under the terms of the quickfixengine.org
** license as defined by quickfixengine.org and appearing in the file
** LICENSE included in the packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.quickfixengine.org/LICENSE for licensing information.
**
** Contact ask@quickfixengine.org if any conditions of this licensing are
** not clear to you.
**
****************************************************************************/

#ifdef _MSC_VER
#pragma warning( disable : 4503 4355 4786 )
#else
#include "config.h"
#endif

#include <UnitTest++.h>
#include "OrderMatcher.h"

TEST( matchFull )
{
  OrderMatcher object;
  Order order1("1", "LNUX", "OWNER1", "TARGET",
               Order::buy, Order::limit, 12.32, 100);
  Order order2("2", "LNUX", "OWNER2", "TARGET",
               Order::sell, Order::limit, 12.32, 100);

  CHECK(object.insert(order1));
  CHECK(object.insert(order2));

  std::queue<Order> orders;
  CHECK(object.match("LNUX", orders));
  CHECK(orders.size() == 2);

  Order matchedOrder1 = orders.front();
  orders.pop();
  Order matchedOrder2 = orders.front();
  orders.pop();

  CHECK(matchedOrder1.getClientID() == "1");
  CHECK(matchedOrder1.isFilled());
  CHECK(matchedOrder1.isClosed());
  CHECK(matchedOrder1.getOpenQuantity() == 0);
  CHECK(matchedOrder1.getExecutedQuantity() == 100);
  CHECK(matchedOrder1.getAvgExecutedPrice() == 12.32);
  CHECK(matchedOrder1.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder1.getLastExecutedQuantity() == 100);

  CHECK(matchedOrder2.getClientID() == "2");
  CHECK(matchedOrder2.isFilled());
  CHECK(matchedOrder2.isClosed());
  CHECK(matchedOrder2.getOpenQuantity() == 0);
  CHECK(matchedOrder2.getExecutedQuantity() == 100);
  CHECK(matchedOrder2.getAvgExecutedPrice() == 12.32);
  CHECK(matchedOrder2.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder2.getLastExecutedQuantity() == 100);
}

TEST( matchPartial )
{
  OrderMatcher object;
  Order order1("1", "LNUX", "OWNER1", "TARGET",
               Order::buy, Order::limit, 12.32, 100);
  Order order2("2", "LNUX", "OWNER2", "TARGET",
               Order::sell, Order::limit, 12.32, 50);
  Order order3("3", "LNUX", "OWNER3", "TARGET",
               Order::sell, Order::limit, 12.30, 50);

  CHECK(object.insert(order1));
  CHECK(object.insert(order2));

  std::queue<Order> orders;
  CHECK(object.match("LNUX", orders));
  CHECK(orders.size() == 2);

  Order matchedOrder1 = orders.front();
  orders.pop();
  Order matchedOrder2 = orders.front();
  orders.pop();

  CHECK(matchedOrder1.getClientID() == "1");
  CHECK(!matchedOrder1.isFilled());
  CHECK(!matchedOrder1.isClosed());
  CHECK(matchedOrder1.getOpenQuantity() == 50);
  CHECK(matchedOrder1.getExecutedQuantity() == 50);
  CHECK(matchedOrder1.getAvgExecutedPrice() == 12.32);
  CHECK(matchedOrder1.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder1.getLastExecutedQuantity() == 50);

  CHECK(matchedOrder2.getClientID() == "2");
  CHECK(matchedOrder2.isFilled());
  CHECK(matchedOrder2.isClosed());
  CHECK(matchedOrder2.getOpenQuantity() == 0);
  CHECK(matchedOrder2.getExecutedQuantity() == 50);
  CHECK(matchedOrder2.getAvgExecutedPrice() == 12.32);
  CHECK(matchedOrder2.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder2.getLastExecutedQuantity() == 50);

  CHECK(object.insert(order3));
  CHECK(object.match("LNUX", orders));
  CHECK(orders.size() == 2);

  matchedOrder1 = orders.front();
  orders.pop();
  Order matchedOrder3 = orders.front();
  orders.pop();

  CHECK(matchedOrder1.getClientID() == "1");
  CHECK(matchedOrder1.isFilled());
  CHECK(matchedOrder1.isClosed());
  CHECK(matchedOrder1.getOpenQuantity() == 0);
  CHECK(matchedOrder1.getExecutedQuantity() == 100);
  CHECK(matchedOrder1.getAvgExecutedPrice() == 12.31);
  CHECK(matchedOrder1.getLastExecutedPrice() == 12.30);
  CHECK(matchedOrder1.getLastExecutedQuantity() == 50);

  CHECK(matchedOrder3.getClientID() == "3");
  CHECK(matchedOrder3.isFilled());
  CHECK(matchedOrder3.isClosed());
  CHECK(matchedOrder3.getOpenQuantity() == 0);
  CHECK(matchedOrder3.getExecutedQuantity() == 50);
  CHECK(matchedOrder3.getAvgExecutedPrice() == 12.30);
  CHECK(matchedOrder3.getLastExecutedPrice() == 12.30);
  CHECK(matchedOrder3.getLastExecutedQuantity() == 50);
}

TEST( matchTimePriority )
{
  OrderMatcher object;
  Order order1("1", "LNUX", "OWNER1", "TARGET",
               Order::sell, Order::limit, 12.32, 50);
  Order order2("2", "LNUX", "OWNER2", "TARGET",
               Order::sell, Order::limit, 12.32, 50);
  Order order3("3", "LNUX", "OWNER3", "TARGET",
               Order::buy, Order::limit, 12.32, 50);

  CHECK(object.insert(order1));
  CHECK(object.insert(order2));

  std::queue<Order> orders;
  CHECK(!object.match("LNUX", orders));
  CHECK(orders.size() == 0);

  CHECK(object.insert(order3));

  CHECK(object.match("LNUX", orders));
  CHECK(orders.size() == 2);

  Order matchedOrder3 = orders.front();
  orders.pop();
  Order matchedOrder1 = orders.front();
  orders.pop();

  CHECK(matchedOrder1.getClientID() == "1");
  CHECK(matchedOrder3.getClientID() == "3");
}

TEST( matchPricePriority )
{  
  OrderMatcher object;
  Order order1("1", "LNUX", "OWNER1", "TARGET",
               Order::sell, Order::limit, 12.32, 50);
  Order order2("2", "LNUX", "OWNER2", "TARGET",
               Order::sell, Order::limit, 12.31, 50);
  Order order3("3", "LNUX", "OWNER3", "TARGET",
               Order::buy, Order::limit, 12.32, 50);

  CHECK(object.insert(order1));
  CHECK(object.insert(order2));

  std::queue<Order> orders;
  CHECK(!object.match("LNUX", orders));
  CHECK(orders.size() == 0);

  CHECK(object.insert(order3));

  CHECK(object.match("LNUX", orders));
  CHECK(orders.size() == 2);

  Order matchedOrder3 = orders.front();
  orders.pop();
  Order matchedOrder2 = orders.front();
  orders.pop();

  CHECK(matchedOrder2.getClientID() == "2");
  CHECK(matchedOrder3.getClientID() == "3");
}

TEST( matchMultiple )
{
  OrderMatcher object;
  Order order1("1", "LNUX", "OWNER1", "TARGET",
               Order::sell, Order::limit, 12.32, 50);
  Order order2("2", "LNUX", "OWNER2", "TARGET",
               Order::sell, Order::limit, 12.30, 50);
  Order order3("3", "LNUX", "OWNER3", "TARGET",
               Order::buy, Order::limit, 12.32, 100);

  CHECK(object.insert(order1));
  CHECK(object.insert(order2));
  CHECK(object.insert(order3));

  std::queue<Order> orders;
  CHECK(object.match("LNUX", orders));
  CHECK(orders.size() == 4);

  Order matchedOrder3_1 = orders.front();
  orders.pop();
  Order matchedOrder2 = orders.front();
  orders.pop();
  Order matchedOrder3_2 = orders.front();
  orders.pop();
  Order matchedOrder1 = orders.front();
  orders.pop();

  CHECK(matchedOrder3_1.getClientID() == "3");
  CHECK(!matchedOrder3_1.isFilled());
  CHECK(!matchedOrder3_1.isClosed());
  CHECK(matchedOrder3_1.getOpenQuantity() == 50);
  CHECK(matchedOrder3_1.getExecutedQuantity() == 50);
  CHECK(matchedOrder3_1.getAvgExecutedPrice() == 12.30);
  CHECK(matchedOrder3_1.getLastExecutedPrice() == 12.30);
  CHECK(matchedOrder3_1.getLastExecutedQuantity() == 50);

  CHECK(matchedOrder2.getClientID() == "2");
  CHECK(matchedOrder2.isFilled());
  CHECK(matchedOrder2.isClosed());
  CHECK(matchedOrder2.getOpenQuantity() == 0);
  CHECK(matchedOrder2.getExecutedQuantity() == 50);
  CHECK(matchedOrder2.getAvgExecutedPrice() == 12.30);
  CHECK(matchedOrder2.getLastExecutedPrice() == 12.30);
  CHECK(matchedOrder2.getLastExecutedQuantity() == 50);

  CHECK(matchedOrder3_2.getClientID() == "3");
  CHECK(matchedOrder3_2.isFilled());
  CHECK(matchedOrder3_2.isClosed());
  CHECK(matchedOrder3_2.getOpenQuantity() == 0);
  CHECK(matchedOrder3_2.getExecutedQuantity() == 100);
  CHECK(matchedOrder3_2.getAvgExecutedPrice() == 12.31);
  CHECK(matchedOrder3_2.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder3_2.getLastExecutedQuantity() == 50);

  CHECK(matchedOrder1.getClientID() == "1");
  CHECK(matchedOrder1.isFilled());
  CHECK(matchedOrder1.isClosed());
  CHECK(matchedOrder1.getOpenQuantity() == 0);
  CHECK(matchedOrder1.getExecutedQuantity() == 50);
  CHECK(matchedOrder1.getAvgExecutedPrice() == 12.32);
  CHECK(matchedOrder1.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder1.getLastExecutedQuantity() == 50);
}

TEST( overMatch )
{
  OrderMatcher object;
  Order order1("1", "LNUX", "OWNER1", "TARGET",
               Order::buy, Order::limit, 12.32, 100);
  Order order2("2", "LNUX", "OWNER2", "TARGET",
               Order::sell, Order::limit, 12.32, 110);
  Order order3("3", "LNUX", "OWNER3", "TARGET",
               Order::buy, Order::limit, 12.32, 100);

  CHECK(object.insert(order1));
  CHECK(object.insert(order2));

  std::queue<Order> orders;
  CHECK(object.match("LNUX", orders));
  CHECK(orders.size() == 2);

  Order matchedOrder1 = orders.front();
  orders.pop();
  Order matchedOrder2 = orders.front();
  orders.pop();

  CHECK(matchedOrder1.getClientID() == "1");
  CHECK(matchedOrder1.isFilled());
  CHECK(matchedOrder1.isClosed());
  CHECK(matchedOrder1.getOpenQuantity() == 0);
  CHECK(matchedOrder1.getExecutedQuantity() == 100);
  CHECK(matchedOrder1.getAvgExecutedPrice() == 12.32);
  CHECK(matchedOrder1.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder1.getLastExecutedQuantity() == 100);

  CHECK(matchedOrder2.getClientID() == "2");
  CHECK(!matchedOrder2.isFilled());
  CHECK(!matchedOrder2.isClosed());
  CHECK(matchedOrder2.getOpenQuantity() == 10);
  CHECK(matchedOrder2.getExecutedQuantity() == 100);
  CHECK(matchedOrder2.getAvgExecutedPrice() == 12.32);
  CHECK(matchedOrder2.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder2.getLastExecutedQuantity() == 100);

  CHECK(object.insert(order3));
  CHECK(object.match("LNUX", orders));
  CHECK(orders.size() == 2);

  Order matchedOrder3 = orders.front();
  orders.pop();
  matchedOrder2 = orders.front();
  orders.pop();

  CHECK(matchedOrder3.getClientID() == "3");
  CHECK(!matchedOrder3.isFilled());
  CHECK(!matchedOrder3.isClosed());
  CHECK(matchedOrder3.getOpenQuantity() == 90);
  CHECK(matchedOrder3.getExecutedQuantity() == 10);
  CHECK(matchedOrder3.getAvgExecutedPrice() == 12.32);
  CHECK(matchedOrder3.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder3.getLastExecutedQuantity() == 10);

  CHECK(matchedOrder2.getClientID() == "2");
  CHECK(matchedOrder2.isFilled());
  CHECK(matchedOrder2.isClosed());
  CHECK(matchedOrder2.getOpenQuantity() == 0);
  CHECK(matchedOrder2.getExecutedQuantity() == 110);
  CHECK(matchedOrder2.getAvgExecutedPrice() == 12.32);
  CHECK(matchedOrder2.getLastExecutedPrice() == 12.32);
  CHECK(matchedOrder2.getLastExecutedQuantity() == 10);

}
