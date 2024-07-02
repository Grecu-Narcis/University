import { User } from "../models/user";

import { ReactNode } from "react";

export type UsersContextType = {
    users: User[];
    addUser: (user: User) => void;
    removeUser: (userId: number) => void;
};

export type UsersContextProviderType = {
    userContext: UsersContextType;
    children: ReactNode;
};
