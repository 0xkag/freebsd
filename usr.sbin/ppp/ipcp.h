/*
 *	    Written by Toshiharu OHNO (tony-o@iij.ad.jp)
 *
 *   Copyright (C) 1993, Internet Initiative Japan, Inc. All rights reserverd.
 *
 * Redistribution and use in source and binary forms are permitted
 * provided that the above copyright notice and this paragraph are
 * duplicated in all such forms and that any documentation,
 * advertising materials, and other materials related to such
 * distribution and use acknowledge that the software was developed
 * by the Internet Initiative Japan.  The name of the
 * IIJ may not be used to endorse or promote products derived
 * from this software without specific prior written permission.
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
 * WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 * $Id: ipcp.h,v 1.18.2.7 1998/02/02 19:32:08 brian Exp $
 *
 *	TODO:
 */

#define	IPCP_MAXCODE	CODE_CODEREJ

#define	TY_IPADDRS	1
#define	TY_COMPPROTO	2
#define	TY_IPADDR	3

/* Domain NameServer and NetBIOS NameServer options */

#define TY_PRIMARY_DNS		129
#define TY_PRIMARY_NBNS		130
#define TY_SECONDARY_DNS	131
#define TY_SECONDARY_NBNS	132

struct in_range {
  struct in_addr ipaddr;
  struct in_addr mask;
  int width;
};

struct ipcpstate {
  struct fsm fsm;			/* The finite state machine */

  int VJInitSlots;			/* Maximum VJ slots */
  int VJInitComp : 1;			/* Slot compression */

  int heis1172 : 1;			/* True if he is speaking rfc1172 */

  struct in_addr his_ipaddr;		/* IP address he's willing to use */
  u_int32_t his_compproto;		/* VJ params he's willing to use */

  struct in_addr want_ipaddr;		/* IP address I'm willing to use */
  u_int32_t want_compproto;		/* VJ params I'm willing to use */

  u_int32_t his_reject;			/* Request codes rejected by peer */
  u_int32_t my_reject;			/* Request codes I have rejected */

#ifndef NOMSEXT
  struct in_addr ns_entries[2];		/* DNS addresses offered */
  struct in_addr nbns_entries[2];	/* NetBIOS NS addresses offered */
#endif

  struct in_range  DefMyAddress;	/* MYADDR spec */

  struct in_range  DefHisAddress;	/* HISADDR spec */
  struct iplist    DefHisChoice;	/* Ranges of HISADDR values */

  struct in_addr   TriggerAddress;	/* Address to suggest in REQ */
  int HaveTriggerAddress : 1;		/* Trigger address specified */

  struct pppThroughput throughput;	/* throughput statistics */
};

extern struct ipcpstate IpcpInfo;

extern void IpcpInit(struct bundle *, struct link *l);
extern void IpcpDefAddress(void);
extern void IpcpUp(void);
extern void IpcpOpen(void);
extern int  ReportIpcpStatus(struct cmdargs const *);
extern void IpcpInput(struct mbuf *);
extern void IpcpAddInOctets(int);
extern void IpcpAddOutOctets(int);
extern int  UseHisaddr(struct bundle *, const char *, int);
extern int  SetInitVJ(struct cmdargs const *);
extern void IpcpDown(void);
