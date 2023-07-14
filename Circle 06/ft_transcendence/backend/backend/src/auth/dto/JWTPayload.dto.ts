import { AuthStatusDTO } from './UserStatus.dto';

export class PayloadDTO {
  login: string;
  id: number;
  status: AuthStatusDTO;
}
