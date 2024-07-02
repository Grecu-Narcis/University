import { FontAwesomeIcon } from '@fortawesome/react-fontawesome';
import { Layout } from '../../shared/components/layout/Layout';

import './DisplayDealersPage.css';
import { faMagnifyingGlass } from '@fortawesome/free-solid-svg-icons';
import { useEffect, useState } from 'react';
import { UserDTO } from '../../types/UserDTO.types';
import { getDealersCountByName, getDealersPage, getDealersPageFilteredByName } from '../../services/Dealers Service/DealersService';
import { DealerCard } from '../../features/Dealer Card/DealerCard';
import InfiniteScroll from 'react-infinite-scroll-component';
import Loading from 'react-loading';

export default function DisplayDealersPage() {
    const [dealersCount, setDealersCount] = useState<number>(0);
    const [isLoadingCount, setIsLoadingCount] = useState<boolean>(true);
    const [dealerName, setDealerName] = useState<string>('');
    const [dealerSearchQuery, setDealerSearchQuery] = useState<string>('');

    const [dealers, setDealers] = useState<UserDTO[]>([]);
    const [isLoadingDealers, setIsLoadingDealers] = useState<boolean>(true);

    const [pageNumber, setPageNumber] = useState<number>(0);

    const fetchDealers = () => {
        getDealersPageFilteredByName(pageNumber, 20, dealerName).then((response) => {
            setDealers([...dealers, ...response]);
            setPageNumber(pageNumber + 1);
        });
    };

    const handleOnChange = (event: any) => {
        setDealerSearchQuery(event.target.value);
    };

    useEffect(() => {
        getDealersPage(pageNumber, 20).then((response) => {
            setDealers([...dealers, ...response]);
            setIsLoadingDealers(false);
            setPageNumber(pageNumber + 1);
        });

        getDealersCountByName(dealerName).then((response) => {
            setDealersCount(response);
            setIsLoadingCount(false);
        });
    }, []);

    useEffect(() => {
        if (dealerSearchQuery.trim() === dealerName) return;

        const timeOutId = setTimeout(() => setDealerName(dealerSearchQuery.trim()), 500);
        return () => clearTimeout(timeOutId);
    }, [dealerSearchQuery]);

    useEffect(() => {
        if (dealerName === '' && dealerSearchQuery) return;

        setIsLoadingCount(true);
        setIsLoadingDealers(true);
        getDealersPageFilteredByName(0, 20, dealerName).then((response) => {
            setDealers(response);
            setPageNumber(1);

            setIsLoadingDealers(false);
        });

        getDealersCountByName(dealerName).then((response) => {
            setDealersCount(response);
            setIsLoadingCount(false);
        });
    }, [dealerName]);

    return (
        <Layout>
            <div className='dealers-page'>
                <div className='title'>
                    <h1>Dealers</h1>
                </div>

                <div className='search'>
                    <FontAwesomeIcon icon={faMagnifyingGlass} className='search-icon' />
                    <input type='text' className='search-bar' placeholder='Search dealers' onChange={handleOnChange}></input>
                </div>

                <div className='dealers-list'>
                    {(isLoadingCount || isLoadingDealers) && (
                        <div className='dealers-loader'>
                            <Loading type='spin' color='black' width={'30px'} height={'30px'} />
                        </div>
                    )}
                    {!isLoadingCount && !isLoadingDealers && dealersCount > 0 && (
                        <InfiniteScroll
                            dataLength={dealers.length}
                            hasMore={dealers.length < dealersCount}
                            next={fetchDealers}
                            className='infinite-scroll-dealers'
                            loader={<div>Loading...</div>}
                            scrollThreshold={0.7}
                        >
                            {dealers.map((dealer) => (
                                <DealerCard key={dealer.id} dealer={dealer} />
                            ))}
                        </InfiniteScroll>
                    )}

                    {!isLoadingCount && !isLoadingDealers && dealersCount === 0 && (
                        <div className='not-found-message'>No dealer found!</div>
                    )}
                </div>
            </div>
        </Layout>
    );
}
