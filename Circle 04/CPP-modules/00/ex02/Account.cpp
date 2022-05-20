#include <iostream>
#include <iomanip>
#include <ctime>
#include "Account.hpp"

Account::Account(int initial_deposit) : _accountIndex(Account::_nbAccounts),
										_amount(initial_deposit), 
										_nbDeposits(0), _nbWithdrawals(0) {
	Account::_nbAccounts++;
	Account::_totalAmount += this->_amount;
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex 
		<< ";amount:" << this->_amount << ";created" << std::endl;
}

/******************************** STATIC FUNC/VAR ********************************/
int Account::_nbAccounts = 0;
int Account::_totalAmount = 0;
int Account::_totalNbDeposits = 0;
int Account::_totalNbWithdrawals = 0;

int	Account::getNbAccounts(void) {return (Account::_nbAccounts);}

int	Account::getTotalAmount(void) {return (Account::_totalAmount);}

int	Account::getNbDeposits(void) {return (Account::_totalNbDeposits);}

int	Account::getNbWithdrawals(void) {return (Account::_totalNbWithdrawals);}

void	Account::displayAccountsInfos(void) {
	Account::_displayTimestamp();
	std::cout << "accounts:" << Account::getNbAccounts() 
		<< ";total:" << Account::getTotalAmount() 
		<< ";deposits:" << Account::getNbDeposits()
		<< ";withdrawals:" << Account::getNbWithdrawals() << std::endl;
}
/*********************************************************************************/

/************************************ ACTIONS ************************************/
void	Account::makeDeposit(int deposit) {
	this->_amount += deposit;
	this->_nbDeposits++;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
		<< ";p_amount:" << this->_amount - deposit
		<< ";deposit:" << deposit
		<< ";amount:" << this->checkAmount()
		<< ";nb_deposits:" << this->_nbDeposits << std::endl;
}

bool	Account::makeWithdrawal(int withdrawal) { 
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
		<< ";p_amount:" << this->_amount << ";withdrawal:";
	if (withdrawal > this->_amount) {
		std::cout << "refused" << std::endl;
		return (false);
	}
	this->_amount -= withdrawal;
	this->_nbWithdrawals++;
	Account::_totalAmount -= withdrawal;
	Account::_totalNbWithdrawals++;
	std::cout << withdrawal << ";amount:" << this->checkAmount()
		<< ";nb_withdrawals:" << this->_nbWithdrawals << std::endl;
	return (true);
}
/*********************************************************************************/

/************************************* UTILS *************************************/
int	Account::checkAmount(void) const {return (this->_amount);}

void	Account::displayStatus(void) const {
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex
		<< ";amount:" << this->_amount
		<< ";deposits:" << this->_nbDeposits
		<< ";withdrawals:" << this->_nbWithdrawals << std::endl;
}

void	Account::_displayTimestamp(void) {
	std::time_t epoch_time = std::time(NULL);
	if (epoch_time == -1) {
		std::cout << "[Error in time()!] ";
		return;
	}

	std::tm calender_time = *std::localtime(&epoch_time);
	std::cout << "[" << (1900 + calender_time.tm_year) 
		<< std::setfill('0') << std::setw(2) << calender_time.tm_mon
		<< std::setfill('0') << std::setw(2) << calender_time.tm_mday << "_"
		<< std::setfill('0') << std::setw(2) << calender_time.tm_hour
		<< std::setfill('0') << std::setw(2) << calender_time.tm_min
		<< std::setfill('0') << std::setw(2) << calender_time.tm_sec << "] ";
}
/*********************************************************************************/

Account::~Account(void) {
	Account::_displayTimestamp();
	std::cout << "index:" << this->_accountIndex 
		<< ";amount:" << this->_amount << ";closed" << std::endl;
}