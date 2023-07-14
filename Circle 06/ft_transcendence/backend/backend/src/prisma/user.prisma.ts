import { Injectable } from '@nestjs/common';
import { PrismaService } from './prisma.service';
import { Prisma, User, BlockedUser } from '@prisma/client';

@Injectable()
export class UserPrismaService {
  constructor(private prisma: PrismaService) {}

  /*	DBGetters_________________________________________________________________*/
  async getUser(
    identifier: Prisma.UserWhereUniqueInput,
    params?: any,
  ): Promise<User | null> {
    const userCount = await this.prisma.user.count();
    if (userCount === 0) {
      return null;
    }

    return identifier.id || identifier.intraLogin || identifier.username
      ? this.prisma.user.findUnique({
          where: identifier,
          include: params,
        })
      : null;
  }

  async getUsers(params: {
    skip?: number;
    take?: number;
    cursor?: Prisma.UserWhereUniqueInput;
    where?: Prisma.UserWhereInput;
    orderBy?: Prisma.UserOrderByWithRelationInput;
  }): Promise<User[]> {
    const { skip, take, cursor, where, orderBy } = params;
    return this.prisma.user.findMany({
      skip,
      take,
      cursor,
      where,
      orderBy,
    });
  }

  /*	DBSetters_________________________________________________________________*/
  async createUser(data: Prisma.UserCreateInput): Promise<User> {
    return this.prisma.user.create({ data });
  }

  async updateUser(
    where: Prisma.UserWhereUniqueInput,
    data: Prisma.UserUpdateInput,
  ): Promise<User> {
    return this.prisma.user.update({ data, where });
  }

  async deleteUser(where: Prisma.UserWhereUniqueInput): Promise<User> {
    return this.prisma.user.delete({ where });
  }


	async addBlockedUser(data: Prisma.BlockedUserCreateInput): Promise<BlockedUser> {
		return this.prisma.blockedUser.create({ data });
	}

	async deleteBlockedUser(where: Prisma.BlockedUserWhereUniqueInput): Promise<BlockedUser> {
		return this.prisma.blockedUser.delete({ where });
	}

	async getBlockedUser(blockedUserId: number, blockedByUserId: number): Promise<BlockedUser> {
		return this.prisma.blockedUser.findFirst({
			where: {
				blockedUserId: blockedUserId,
				blockedByUserId: blockedByUserId,
			}
		});
	}

  async getBlockedUsers(userID: number): Promise<any> {
    return this.prisma.blockedUser.findMany({
      where: {
        blockedByUserId: userID,
      },
      select: {
        blockedUser: {
          select: {
            id: true,
            username: true,
          },
        },
      },
    });
  }
}
