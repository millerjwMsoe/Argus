/*
 * File: irreceiver.h
 * Description: Common interface for IR receivers
 */

#ifndef IRRECEIVER_H_
#define IRRECEIVER_H_

class IRReceiver {
public:

  // return true if IR light was detected
  virtual bool lightDetected() = 0;

  virtual ~IRReceiver();

};

#endif /* IRRECEIVER_H_ */
