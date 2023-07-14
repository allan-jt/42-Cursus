import { Injectable } from '@nestjs/common';
import { ChatPrismaService } from './prisma.service';
import { Channel, Message, Participant, Role } from '@prisma/client';
import { ParticipantService } from './participant.service';
import { hashPassword } from 'src/prisma/bcrypt';

@Injectable()
export class ChatService {
  constructor(
    private chatPrismaService: ChatPrismaService,
    private participantService: ParticipantService,
  ) {}

  /* Channel */
  async createChannel(
    name: string,
    ownerID: number,
    isDirect: boolean,
    isPublic: boolean,
    password?: string,
  ) {
    password = password ? await hashPassword(password) : '';
    const data = {
      name: name,
      isDirect: isDirect,
      isPublic: isPublic,
      password: password,
    };

    try {
      //create channel
      const channel: Channel = await this.chatPrismaService.createChannel(data);

      //assign owner to channel
      const owner: Participant =
        await this.participantService.createChannelParticipant(
          ownerID,
          channel.id,
          Role.OWNER,
        );

      return channel;
    } catch (err) {
      console.log(err);
    }
  }

  async getChannelByID(id: number): Promise<Channel> {
    try {
      return await this.chatPrismaService.getChannel({ id: id });
    } catch (err) {
      console.log(err);
    }
  }

  async getAllPublicChannels() {
    try {
      return await this.chatPrismaService.getAllPublicChannels();
    } catch (err) {
      console.log(err);
    }
  }

  async getAllPublicChannelsNotJoined(user_id: number) {
    try {
      return await this.chatPrismaService.getAllPublicChannelsNotJoined(
        user_id,
      );
    } catch (err) {
      console.log(err);
    }
  }

  async getAllJoinedChannels(user_id: number) {
    try {
      return await this.chatPrismaService.getAllJoinedChannels(user_id);
    } catch (err) {
      console.log(err);
    }
  }

  async updateChannelName(channelID: number, newName: string): Promise<void> {
    try {
      await this.chatPrismaService.updateChannel(
        { id: channelID },
        { name: newName },
      );
    } catch (err) {
      console.log(err);
    }
  }

  async updateChannelPassword(
    channelID: number,
    password: string,
  ): Promise<void> {
    password = password ? await hashPassword(password) : '';
    try {
      await this.chatPrismaService.updateChannel(
        { id: channelID },
        { password: password },
      );
    } catch (err) {
      console.log(err);
    }
  }

  async addUserToChannel(userID: number, channelID: number, role: Role) {
    try {
      return await this.participantService.createChannelParticipant(
        userID,
        channelID,
        role,
      );
    } catch (err) {
      console.log(err);
    }
  }

  async removeUserFromChannel(
    userID: number,
    channelID: number,
  ): Promise<void> {
    try {
      const temp = await this.participantService.getParticipant(
        userID,
        channelID,
      );
      await this.chatPrismaService.deleteParticipant({
        id: temp.id,
      });
    } catch (err) {
      console.log(err);
    }
  }

  async banUserFromChannel(userID: number, channelID: number) {
    try {
      const participant = await this.participantService.getParticipant(
        userID,
        channelID,
      );
      await this.chatPrismaService.updateParticipant(
        { id: participant.id },
        { isBanned: true },
      );
    } catch (err) {
      console.log(err);
    }
  }

  async unbanUserFromChannel(userID: number, channelID: number) {
    try {
      const participant = await this.participantService.getParticipant(
        userID,
        channelID,
      );
      await this.chatPrismaService.updateParticipant(
        { id: participant.id },
        { isBanned: false },
      );
    } catch (err) {
      console.log(err);
    }
  }

  async inviteUserToChannel(userID: number, channelID: number) {
    try {
      const participant = await this.participantService.getParticipant(
        userID,
        channelID,
      );
      await this.chatPrismaService.updateParticipant(
        { id: participant.id },
        { role: Role.INVITED },
      );
    } catch (err) {
      console.log(err);
    }
  }

  async uninviteUserFromChannel(userID: number, channelID: number) {
    try {
      const participant = await this.participantService.getParticipant(
        userID,
        channelID,
      );
      await this.chatPrismaService.deleteParticipant({ id: participant.id });
    } catch (err) {
      console.log(err);
    }
  }

  async muteUserInChannel(
    userID: number,
    channelID: number,
    muteDurationMinutes: number,
  ) {
    const now = new Date();
    const muteFinishAt = new Date(now.getTime() + muteDurationMinutes * 60000);

    try {
      const participant = await this.participantService.getParticipant(
        userID,
        channelID,
      );
      await this.chatPrismaService.updateParticipant(
        { id: participant.id },
        { isMuted: true, muteFinishAt: muteFinishAt },
      );
    } catch (err) {
      console.log(err);
    }
  }

  async unmuteUserInChannel(userID: number, channelID: number) {
    try {
      const participant = await this.participantService.getParticipant(
        userID,
        channelID,
      );
      await this.chatPrismaService.updateParticipant(
        { id: participant.id },
        { isMuted: false, muteFinishAt: null },
      );
    } catch (err) {
      console.log(err);
    }
  }

  async makeUserAdminInChannel(userID: number, channelID: number) {
    const participant = await this.participantService.getParticipant(
      userID,
      channelID,
    );
    if (!participant) throw new Error('Participant not found');
    try {
      await this.chatPrismaService.updateParticipant(
        { id: participant.id },
        { role: Role.ADMIN },
      );
    } catch (err) {
      console.log(err);
    }
  }

  async removeUserAdminInChannel(userID: number, channelID: number) {
    try {
      const participant = await this.participantService.getParticipant(
        userID,
        channelID,
      );
      await this.chatPrismaService.updateParticipant(
        { id: participant.id },
        { role: Role.MEMBER },
      );
    } catch (err) {
      console.log(err);
    }
  }

  async deleteChannel(channelID: number): Promise<Channel> {
    try {
      await this.chatPrismaService.deleteParticipantsInChannel(channelID);
      await this.chatPrismaService.deleteMessagesInChannel(channelID);
      return await this.chatPrismaService.deleteChannel({ id: channelID });
    } catch (err) {
      console.log(err);
    }
  }

  async upgradeUserToMember(user_id: number, channel_id: number) {
    const participant = await this.participantService.getParticipant(
      user_id,
      channel_id,
    );
    if (participant) {
      try {
        await this.chatPrismaService.updateParticipant(
          { id: participant.id },
          { role: Role.MEMBER },
        );
      } catch (err) {
        console.log(err);
      }
    } else {
      console.log('Participant not found');
    }
  }

  async getAllChannelsUserIsInvitedTo(userID: number) {
    try {
      return this.chatPrismaService.getAllChannelsUserIsInvitedTo(userID);
    } catch (err) {
      console.log(err);
    }
  }

  async getAvailableUsersNotInChannel(channelID: number) {
    try {
      return await this.chatPrismaService.getAvailableUsersNotInChannel(
        channelID,
      );
    } catch (err) {
    //   console.log(err);
    }
  }

  async getDirectChannelBetweenTwoUsers(user_id: number, otherUserID: number) {
    try {
      return await this.chatPrismaService.getDirectChannelBetweenUsers(
        user_id,
        otherUserID,
      );
    } catch (err) {
    //   console.log(err);
    }
  }
}
