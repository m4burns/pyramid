class TestMapper(pyramid.PythonMapper):
	ctr = 0
	def mapNote(self, port, note):
		print "Called mapNote: ", port, " ", note.channel, " ", note.note, " ", note.velocity, " ", note.state
		if note.state == 1:
			self.ctr += 1
		note.note += self.ctr
		self.sendNote(1, note)

m = TestMapper()
m.selectPorts("0 <= 'VirMIDI 2-0', 1 => 'TiMidity - TiMidity port 0', 2 <= 'LPK25 - LPK25 MIDI 1'")

