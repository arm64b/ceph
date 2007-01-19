// -*- mode:C++; tab-width:8; c-basic-offset:2; indent-tabs-mode:t -*- 
/*
 * Ceph - scalable distributed file system
 *
 * Copyright (C) 2004-2006 Sage Weil <sage@newdream.net>
 *
 * This is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License version 2.1, as published by the Free Software 
 * Foundation.  See file COPYING.
 * 
 */


#ifndef __MDIREXPIREREQ_H
#define __MDIREXPIREREQ_H

typedef struct {
  inodeno_t ino;
  int nonce;
  int from;
} MDirExpireReq_st;

class MDirExpire : public Message {
  MDirExpireReq_st st;

 public:
  inodeno_t get_ino() { return st.ino; }
  int get_from() { return st.from; }
  int get_nonce() { return st.nonce; }

  MDirExpire() {}
  MDirExpire(inodeno_t ino, int from, int nonce) :
    Message(MSG_MDS_DIREXPIREREQ) {
    st.ino = ino;
    st.from = from;
    st.nonce = nonce;
  }
  virtual char *get_type_name() { return "DirExR";}
  
  virtual void decode_payload(crope& s) {
    s.copy(0, sizeof(st), (char*)&st);
  }
  virtual void encode_payload(crope& s) {
    s.append((char*)&st,sizeof(st));
  }
};

#endif
