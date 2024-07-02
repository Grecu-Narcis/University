import { User } from "../models/user"

export type PagingContextProps = {
    currentUsers: User[],
    setCurrentUsers: (newUsers: User[]) => void,
    currentPage: number,
    setCurrentPage: (newPage: number) => void,
    pageSize: number,
}