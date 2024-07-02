import { useEffect, useState } from 'react';
import Loading from 'react-loading';
import InfiniteScroll from 'react-infinite-scroll-component';
import { getUsersCount, getUsersPage } from '../../services/Users Service/UsersService';
import { UserDTO } from '../../types/UserDTO.types';
import { UserCard } from '../Display Users/UserCard';

import './UsersGallery.css';

export default function UsersGallery() {
    const [users, setUsers] = useState<UserDTO[]>([]);
    const [totalCount, setTotalCount] = useState<number>(0);
    const [page, setPage] = useState<number>(1);

    const pageSize = 30;

    const [isLoadingUsers, setIsLoadingUsers] = useState<boolean>(true);
    const [isLoadingTotalCount, setIsLoadingTotalCount] = useState<boolean>(true);

    const fetchCars = () => {
        getUsersPage(page, true, pageSize).then((response) => {
            setUsers([...users, ...response]);
            setPage(page + 1);
        });
    };

    useEffect(() => {
        getUsersPage(0, true, pageSize).then((response) => {
            setUsers(response);
            setIsLoadingUsers(false);
        });

        getUsersCount().then((response) => {
            setTotalCount(response);
            setIsLoadingTotalCount(false);
        });
    }, []);

    if (isLoadingUsers || isLoadingTotalCount) return <Loading type='spin' width={'40px'} color='black' />;

    return (
        <InfiniteScroll
            data-testid='users-infinite-scroll'
            next={fetchCars}
            hasMore={users.length < totalCount}
            loader={<Loading type='spin' color='black' width={'40px'} />}
            dataLength={users.length}
            className='all-users-scroll'
        >
            {users.map((user, index) => (
                <UserCard key={index} givenUser={user} />
            ))}
        </InfiniteScroll>
    );
}
