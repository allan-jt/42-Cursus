import { ExecutionContext, Injectable } from '@nestjs/common';
import { AuthGuard } from '@nestjs/passport';

@Injectable()
export class NonLoggedAuthGuard extends AuthGuard('non-logged') {
  constructor() {
    super();
  }

  canActivate(context: ExecutionContext) {
    return super.canActivate(context);
  }
}
