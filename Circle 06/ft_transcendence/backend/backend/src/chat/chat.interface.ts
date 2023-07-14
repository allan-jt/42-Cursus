export interface CreateChannelPayload {
  name: string;
  ownerID: number;
  isDirect: boolean;
  isPublic: boolean;
  password?: string;
	otherUserID?: number;
}

export interface ChatWithFriend {
	other_user_id: number;
}

export interface UpdateChannelNamePayload {
  channel_id: number;
  name: string;
}

export interface UpdateChannelPasswordPayload {
  channel_id: number;
  password: string;
}

export interface ModifyArrayPayload {
  channel_id: number;
  user_id: number;
  password?: string;
}

export interface DeleteChannelPayload {
  channel_id: number;
}

export interface CreateMessagePayload {
  sender_id: number;
  channel_id: number;
  messageBody: string;
}

export interface SendMessage {
	id: number;
  sender_id: number;
  sender_username: string;
  channel_id: number;
  messageBody: string;
  sentAt: Date;
}

export interface GetMessagesInChannelPayload {
  channel_id: number;
}
