/* ************************************************************************* */
/*                                                                           */
/*                      Webserv                           :::      ::::::::  */
/*   By:                                                :+:      :+:    :+:  */
/*     bnaji <bnaji@student.42abudhabi.ae>            +:+ +:+         +:+    */
/*     mpatel <mpatel@student.42abudhabi.ae>        +#+  +:+       +#+       */
/*     athekkep <athekkep@student.42abudhabi.ae>  +#+#+#+#+#+   +#+          */
/*                                                     #+#    #+#            */
/*   Created: 2022/11/19 14:48:47                     ###   ########.AD      */
/*                                                                           */
/* ************************************************************************* */

#ifndef TIMER_HPP
#define TIMER_HPP

#include "../webserv.hpp"
#include <iomanip>

class Timer {
  private:
    struct timeval  _begin;
    struct timeval  _end;
    double          _startTime;
    double          _stopTime;
    double          _elapsed;
    time_t          _now;

	public:
		Timer();
		Timer(Timer const &src);
		Timer &operator=(Timer const &rhs);
    ~Timer();

    void          start();
    void          stop();
  
//  Getters
    double        getCurTime();
    STRING        getCurTimeString();
    double const  &getStartTime() const;
    double const  &getStopTime() const;
    double const  &getElapsed() const;
};

std::ostream &			operator<<(std::ostream &o, Timer const &i);

#endif