// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerLibrary.h"

FVector UPlayerLibrary::PlayerVelocity( float _max_velocity, FVector _current_velocity, float _change_amount )
{
	FVector new_velocity{ 0,0,0 };

	new_velocity.Y += _change_amount;
	if( abs( _current_velocity.Y + new_velocity.Y ) > abs( _current_velocity.Y ) && abs( _current_velocity.Y ) > _max_velocity )
		new_velocity.Y = 0;

	return new_velocity;
}

FVector UPlayerLibrary::DynamicCameraOffset( FVector _velocity, FVector _offsetSpeed, FVector _multiplier, float _deltaTime, FVector _currentPosition )
{
	FVector newOffset = _currentPosition;
	FVector targetOffset{};

	targetOffset.X = _velocity.Length() * _multiplier.X * -1;                                   // Zoom
	newOffset.X += ( targetOffset.X - _currentPosition.X ) * _offsetSpeed.X * _deltaTime;      //  Zoom
																							  //
	targetOffset.Y = _velocity.Y * _multiplier.Y * -1;										 // Horizontal
	newOffset.Y += ( targetOffset.Y - _currentPosition.Y ) * _offsetSpeed.Y * _deltaTime;   //  Horizontal
	                                                                                       //
	targetOffset.Z = _velocity.Z * _multiplier.Z;										  // Vertical
	newOffset.Z += ( targetOffset.Z - _currentPosition.Z ) * _offsetSpeed.Z * _deltaTime;//  Vertical

	return newOffset;
}

FVector UPlayerLibrary::OptimalRopeDirection( FVector _velocity )
{
	FVector dir = FVector( _velocity.X, -_velocity.Z, _velocity.Y );
	if ( dir.Z < 0 )
		dir *= -1;

	dir.Normalize();
	return dir;
}
