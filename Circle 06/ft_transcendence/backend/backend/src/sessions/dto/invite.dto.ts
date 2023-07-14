export enum InviteStatus {
  invitee_no_exist,
  invitee_no_available,
  inviter_no_exist,
  inviter_no_available,
  invite_sent,
  response_received,
}

export interface Invite {
  inviterName: string;
  inviteeName: string;
  status: InviteStatus;
  accept: boolean;
}
