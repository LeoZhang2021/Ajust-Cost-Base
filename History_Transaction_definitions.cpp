#include <cassert>
#include <iomanip>
#include <iostream>

#include "project4.hpp"
#include "History.hpp"
#include "Transaction.hpp"

////////////////////////////////////////////////////////////////////////////////
// Definitions for Transaction class
////////////////////////////////////////////////////////////////////////////////
//
//

// Constructor
// TASK 1
//
Transaction::Transaction( std::string ticker_symbol,  unsigned int day_date, unsigned int month_date,  unsigned year_date, 
        bool buy_sell_trans,  unsigned int number_shares, double trans_amount ){

    symbol = ticker_symbol;
    day = day_date;
    month = month_date;
    year = year_date;

    if(buy_sell_trans == true){

      trans_type = "Buy";

    }else{

      trans_type = "Sell";

    }

    shares = number_shares;
    amount = trans_amount;
    trans_id = assigned_trans_id;
    assigned_trans_id++;

    p_next = nullptr;

    acb = get_acb();
    acb_per_share = get_share_balance();
    cgl = get_cgl();
    share_balance = get_share_balance();

}


// Destructor
// TASK 1
//
Transaction::~Transaction(){
  //need to delete any memory?

}

// Overloaded < operator.
// TASK 2
//

bool Transaction::operator < (Transaction const & other){

  //compare transaction1 and transaction2
  //However transaction is an object, so we need to overload
  //"this-> refers to the transaction we are currently in, and "other." refers to other transactions
  //other refers to the right operand (transaction 2), 
  //while directly using variables refers to left operand(transaction 1)

  if(year < other.get_year()){  

    return true;

  }else if(year == other.get_year()){

    if(month < other.get_month()){

      return true;

    }else if(month == other.get_month()){

      if(day < other.get_day()){

        return true;

      }
    }
  }


  return false;

}

// GIVEN
// Member functions to get values.
//
std::string Transaction::get_symbol() const { return symbol; }
unsigned int Transaction::get_day() const { return day; }
unsigned int Transaction::get_month() const { return month; }
unsigned int Transaction::get_year() const { return year; }
unsigned int Transaction::get_shares() const { return shares; }
double Transaction::get_amount() const { return amount; }
double Transaction::get_acb() const { return acb; }
double Transaction::get_acb_per_share() const { return acb_per_share; }
unsigned int Transaction::get_share_balance() const { return share_balance; }
double Transaction::get_cgl() const { return cgl; }
bool Transaction::get_trans_type() const { return (trans_type == "Buy") ? true: false ; }
unsigned int Transaction::get_trans_id() const { return trans_id; }
Transaction *Transaction::get_next() { return p_next; }

// GIVEN
// Member functions to set values.
//
void Transaction::set_acb( double acb_value ) { acb = acb_value; }
void Transaction::set_acb_per_share( double acb_share_value ) { acb_per_share = acb_share_value; }
void Transaction::set_share_balance( unsigned int bal ) { share_balance = bal ; }
void Transaction::set_cgl( double value ) { cgl = value; }
void Transaction::set_next( Transaction *p_new_next ) { p_next = p_new_next; }

// GIVEN
// Print the transaction.
//
void Transaction::print() {
  std::cout << std::fixed << std::setprecision(2);
  std::cout << std::setw(4) << get_trans_id() << " "
    << std::setw(4) << get_symbol() << " "
    << std::setw(4) << get_day() << " "
    << std::setw(4) << get_month() << " "
    << std::setw(4) << get_year() << " ";


  if ( get_trans_type() ) {
    std::cout << "  Buy  ";
  } else { std::cout << "  Sell "; }

  std::cout << std::setw(4) << get_shares() << " "
    << std::setw(10) << get_amount() << " "
    << std::setw(10) << get_acb() << " " << std::setw(4) << get_share_balance() << " "
    << std::setw(10) << std::setprecision(3) << get_acb_per_share() << " "
    << std::setw(10) << std::setprecision(3) << get_cgl()
    << std::endl;
}


////////////////////////////////////////////////////////////////////////////////
// Definitions for the History class
////////////////////////////////////////////////////////////////////////////////
//
//


// Constructor
// TASK 3
//
History::History(){

  p_head = nullptr;

}

// Destructor
// TASK 3
//
History::~History(){

  Transaction * p_tmp  = p_head;

  while ( p_head != nullptr ) //
  {
     p_tmp = p_tmp->get_next();

     delete p_head;

     p_head = p_tmp;
  }

}


// read_history(...): Read the transaction history from file. one transaction at a time
//call insert(...) once for each transaction to build the complete linked list
// TASK 4
//
void History::read_history(){

  ece150::open_file();
  Transaction *trans = nullptr;

  while(ece150::next_trans_entry()){

    std::string sym = ece150::get_trans_symbol();
    unsigned int day = ece150::get_trans_day();
    unsigned int  month= ece150::get_trans_month();
    unsigned int  year = ece150::get_trans_year();
    unsigned int  shares = ece150::get_trans_shares();
    bool type = ece150::get_trans_type();
    double amount = ece150::get_trans_amount();

    trans = new Transaction(sym, day, month, year, type, shares, amount);

    insert(trans);

  }

  ece150::close_file();

}

// insert(...): Insert transaction into linked list.
// TASK 5
//
void History::insert(Transaction *p_new_trans){ //parameter is a pointer to a transaction(a node)

  if(p_head == nullptr){

    this->p_head = p_new_trans;
    
  }else{

    Transaction * p_traverse = p_head;

    while(p_traverse ->get_next() != nullptr){

      p_traverse = p_traverse->get_next();
    }

    p_traverse->set_next(p_new_trans);

  }
}

// sort_by_date(): Sort the linked list by trade date.
// TASK 6
//
void History::sort_by_date(){

  /*

  Transaction * p_sorted = nullptr;
  Transaction * p_temp = nullptr;

  p_sorted = p_head;

  Transaction * p_1  = p_sorted -> get_next();
  Transaction * p_2  = p_1 -> get_next();

  if(p_head != nullptr){

    while(p_1 != nullptr){

      p_temp = p_sorted -> get_next();
      p_2 = p_sorted;

      while(*p_temp < *p_2){

        p_temp = p_temp -> get_next();
        p_1 = p_1 -> get_next();

      }
      
      if(p_temp == p_2){

        p_1 = p_1->get_next();
        p_2 = p_2->get_next();

      }else{

          p_1->set_next(p_2->get_next());
          p_2->set_next(p_temp);
          p_1->set_next(p_2);
          p_2 = p_1->get_next();

      } 
    }

    p_head=p_sorted->get_next();  
  }

  delete p_sorted;
  delete p_1;
  delete p_2;
  delete p_temp;

  p_sorted = nullptr;
  p_1 = nullptr;
  p_2 = nullptr;
  p_temp = nullptr;

  */
  /*

  Transaction * p_insert = nullptr;
  Transaction * p_sorted = nullptr;
  Transaction * p_temp = nullptr;

  p_sorted = p_head;

  p_sorted -> set_next(nullptr);

  while(p_head != nullptr){

    p_head = p_head -> get_next();
    p_insert = p_head;

    p_insert -> set_next(nullptr);

    if(*p_insert < *p_sorted){

      p_insert -> set_next(p_sorted);
      p_sorted = p_insert;

    }else{

        p_temp = p_sorted;

        while((*(p_temp -> get_next()) < *p_insert)||(p_temp -> get_next() != nullptr)){

          p_temp = p_temp -> get_next();

        }

        p_insert -> set_next(p_temp -> get_next());
        p_temp -> set_next(p_insert);
        p_sorted = p_temp;

    }

  }

  p_head = p_sorted;

  delete p_insert;
  delete p_sorted;
  delete p_temp;

  p_insert = nullptr;
  p_sorted = nullptr;
  p_temp = nullptr;

  */

  /*

  Transaction * p_front = nullptr; //current node to insert (p_insert)
  Transaction * p_head_new = nullptr; //store sorted linked list (p_sorted)

  while(p_head != nullptr){

    p_front = p_head;
    p_head = p_head->get_next(); //temp
    p_front->set_next(nullptr);  

    if(p_head_new == nullptr){

      p_head_new = p_front;
      p_front = nullptr;

    }else{

      //insert

      if(*p_front < *p_head_new){

        p_front -> set_next(p_head_new);
        p_head_new = p_front;

      }else{

        Transaction * p_traverse = p_head_new; //store temporary p_head_new so we can iterate through it

        while((*(p_traverse->get_next()) < *p_front) && (p_traverse != nullptr)){

          p_traverse = p_traverse->get_next();

        }

        p_front->set_next(p_traverse->get_next());
        p_traverse->set_next(p_front);
        p_front = nullptr;
        p_traverse = nullptr;
      
      }

    }

  }

  p_head = p_head_new;

  */

}

// update_acb_cgl(): Updates the ACB and CGL values.
// TASK 7
//

void History::update_acb_cgl(){
        Transaction * p_new_1 = p_head;
        Transaction * p_new_2 = p_head;

        //p_new_1->set_acb(get_abc());
        //p_new_1->set_acb_per_share(get_acb_per_share());
        //p_new_1->set_share_balance(get_share_balance());
        //p_new_1->set_cgl(get_cgl());

        while(p_new_2 != nullptr){
          if(p_new_2 != p_new_1){
            if(p_new_2->get_trans_type()){
              p_new_2->set_cgl(0.000);
              p_new_2->set_acb(p_new_1->get_acb() + p_new_2->get_amount());
              p_new_2->set_share_balance(p_new_1->get_share_balance() +p_new_2->get_shares() );
              p_new_2->set_acb_per_share(p_new_2->get_acb()/p_new_2->get_share_balance());
              }else{
              p_new_2->set_acb(p_new_1->get_acb() - (p_new_1 -> get_acb_per_share()*p_new_2->get_shares()));
              p_new_2->set_acb_per_share(p_new_2->get_acb()/p_new_2->get_share_balance());
              p_new_2->set_share_balance(p_new_1->get_share_balance() - p_new_2->get_shares() );
              p_new_2->set_cgl(p_new_2->get_amount() - (p_new_2->get_shares() * p_new_1->get_acb_per_share()));
              }
            }else{
              
              p_new_2->set_acb(p_new_2->get_amount());
              p_new_2->set_acb_per_share(p_new_2->get_acb()/p_new_2->get_share_balance());
              p_new_2->set_share_balance(p_new_2->get_shares());
              

            }
            p_new_1 = p_new_2;
            p_new_2 = p_new_2->get_next();

        }
        p_new_1 = nullptr;
        delete p_new_1;
}
/*
void History::update_acb_cgl()
{
    Transaction * before= get_p_head();
    Transaction * after = get_p_head();

    while (after != nullptr){

        if (after == before){

          //set 4 variables

            after->set_acb(after->get_amount());
            after->set_share_balance(after->get_shares());
            after->set_acb_per_share(after->get_acb() / after->get_share_balance());
            after -> set_cgl(0);

            after= after->get_next();

        }else{

          if(after -> get_trans_type() == true){

            after -> set_share_balance(after->get_shares() + before -> get_share_balance());
            after -> set_acb(before -> get_acb() + after -> get_amount());
            after -> set_cgl(0);

          }else{

            after->set_share_balance(before->get_share_balance() - after->get_shares());
            after->set_acb(before->get_acb() - (after->get_shares() * (before->get_acb_per_share())));

          }

          after->set_acb_per_share(after->get_acb() / after->get_share_balance());

          if(after -> get_trans_type() == false){

            after->set_cgl(after->get_amount() - (after->get_shares()*(before->get_acb_per_share())));

          }

          before = after;
          after = after->get_next();
           
        }
    }

    before = nullptr;
    delete before;

}
*/

// compute_cgl(): )Compute the ACB, and CGL.
// TASK 8
double History::compute_cgl(unsigned int year){

  Transaction * p = get_p_head();
  double cgl = 0;

  if(p != nullptr){

    while(p != nullptr){

      if(p -> get_year() == year){ //same year

        cgl = cgl + p -> get_cgl(); //adding cgl of all dates in this year

      }

      p = p -> get_next(); //next p_head

    }

    p = nullptr;
    delete p;

    return cgl;

  }

  return 0;

}

// print() Print the transaction history.
//TASK 9
//
void History::print(){

  std::cout<<"==========BEGIN TRANSACTION HISTORY=========="<<std::endl;

    Transaction * head = get_p_head();
    while (head != NULL)
    {
 
        head->print();
        head = head->get_next();
    }

    head = nullptr;
    delete head;


  std::cout<<"==========END TRANSACTION HISTORY=========="<<std::endl;

}


// GIVEN
// get_p_head(): Full access to the linked list.
//
Transaction *History::get_p_head() { return p_head; }
