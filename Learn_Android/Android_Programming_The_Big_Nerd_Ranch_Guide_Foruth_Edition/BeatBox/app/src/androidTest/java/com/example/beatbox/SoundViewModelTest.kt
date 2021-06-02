package com.example.beatbox

import org.hamcrest.core.Is
import org.junit.Before

import org.junit.Assert.*
import org.junit.Test
import org.mockito.Mockito

class SoundViewModelTest {

    private lateinit var beatBox: BeatBox
    private lateinit var sound: Sound
    private lateinit var subject: SoundViewModel

    @Before
    fun setUp() {
        beatBox = Mockito.mock(BeatBox::class.java)
        sound = Sound("assetPath")
        subject = SoundViewModel(beatBox)
        subject.sound = sound
    }

    @Test
    fun exposesSoundNameAsTitle() {
        assertThat(subject.title, Is.`is`(sound.name))
    }

    @Test
    fun callsBeatBoxPlayOnButtonClicked() {
        subject.onButtonClick()
        Mockito.verify(beatBox).play(sound)
    }
}