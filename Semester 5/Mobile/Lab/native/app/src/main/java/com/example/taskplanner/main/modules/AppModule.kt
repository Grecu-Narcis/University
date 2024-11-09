package com.example.taskplanner.main.modules

import com.example.taskplanner.main.repository.InMemoryRepository
import dagger.Module
import dagger.Provides
import dagger.hilt.InstallIn
import dagger.hilt.components.SingletonComponent
import javax.inject.Singleton

@Module
@InstallIn(SingletonComponent::class)
class AppModule {
    @Provides
    @Singleton
    fun provideTaskRepository(): InMemoryRepository {
        return InMemoryRepository()
    }
}