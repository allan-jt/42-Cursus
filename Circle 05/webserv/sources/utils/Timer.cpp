/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:50:51                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#include "../../includes/utils/Timer.hpp"

/***********************CANONICAL & OTHER CONSTRINGUCTORS***********************/
Timer::Timer() : _startTime(0), _stopTime(0), _elapsed(0) {}

Timer::Timer(const Timer &src) {*this = src;}

Timer::~Timer() {}

Timer &Timer::operator=(Timer const &rhs) {
	if (this != &rhs) {
		this->_begin = rhs._begin;
		this->_end = rhs._end;
		this->_startTime = rhs._startTime;
		this->_stopTime = rhs._stopTime;
		this->_elapsed = rhs._elapsed;
	}
	return *this;
}

std::ostream  &operator<<(std::ostream &o, Timer const &i) {
	o << PURPLE << "Time measured : " << std::setprecision(5) << std::fixed 
    << YELLOW << i.getElapsed() << WHITE << " s" << RESET << std::endl;
	return o;
}

/*********************************MAIN FUNCTIONS*******************************/
void  Timer::start() {
  gettimeofday(&_begin, NULL);
  _startTime = _begin.tv_sec + _begin.tv_usec * 1e-6;
}

void  Timer::stop() {
  gettimeofday(&_end, NULL);
  _stopTime = _end.tv_sec + _end.tv_usec * 1e-6;
  _elapsed = _stopTime - _startTime;
}

double  Timer::getCurTime() {
  struct timeval  end;
  gettimeofday(&end, NULL);
  return ((end.tv_sec - _begin.tv_sec) + (end.tv_usec - _begin.tv_usec) * 1e-6);
}

STRING  Timer::getCurTimeString() {
  _now = time(NULL);

  //trim newline
  STRING tmp(ctime(&_now));
  tmp.erase(tmp.length()-1, 1);
  
  return tmp;
}

/************************************GETTERS***********************************/
double const  &Timer::getStartTime() const {return _startTime;}

double const  &Timer::getStopTime() const {return _stopTime;}

double const  &Timer::getElapsed() const {return _elapsed;}